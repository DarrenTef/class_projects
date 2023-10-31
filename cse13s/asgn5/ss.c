#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include "numtheory.h"
#include <stdlib.h>
#include "randstate.h"
#include "ss.h"
#include <inttypes.h>

void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    uint64_t p_bits, q_bits;
    mpz_t p_p, q_p, p_s, pq;
    mpz_inits(p_p, q_p, p_s, pq, NULL);
    p_bits = (rand() % (((2 * nbits) / 5) - (nbits / 4) + 1)) + (nbits / 4);
    q_bits = nbits - (p_bits * 2);
    make_prime(p, p_bits, iters);
    make_prime(q, q_bits, iters);
    mpz_sub_ui(p_p, p, 1);
    mpz_sub_ui(q_p, q, 1);

    if (mpz_divisible_p(p, q_p) != 0) {
        make_prime(p, p_bits, iters);
        make_prime(q, q_bits, iters);
    }

    if (mpz_divisible_p(q, p_p) != 0) {
        make_prime(p, p_bits, iters);
        make_prime(q, q_bits, iters);
    }

    mpz_mul(pq, p, q);
    mpz_mul(n, pq, p);

    mpz_clears(p_p, q_p, p_s, pq, NULL);
}

void ss_make_priv(mpz_t d, mpz_t pq, mpz_t p, mpz_t q) {
    mpz_t t_p, t_q, t_n, gcd_v, lcm, n, p_s;
    mpz_inits(t_p, t_q, t_n, gcd_v, lcm, n, p_s, NULL);

    mpz_sub_ui(t_p, p, 1);
    mpz_sub_ui(t_q, q, 1);
    mpz_mul(t_n, t_p, t_q);
    mpz_abs(t_n, t_n);
    gcd(gcd_v, t_p, t_q);
    mpz_fdiv_q(lcm, t_n, gcd_v);
    mpz_mul(pq, p, q);
    mpz_mul(n, pq, p);
    mod_inverse(d, n, lcm);

    mpz_clears(t_p, t_q, t_n, gcd_v, lcm, n, p_s, NULL);
}

void ss_write_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%s\n", username);
}

void ss_write_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", pq);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%s\n", n, username);
}

void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", pq, d);
}

void ss_encrypt(mpz_t c, mpz_t m, mpz_t n) {
    pow_mod(c, m, n, n);
}

void ss_encrypt_file(FILE *infile, FILE *outfile, mpz_t n) {
    // Calculating for the value of k
    uint64_t k;
    mpz_t n_t, m, cypher;
    mpz_inits(n_t, m, cypher, NULL);
    mpz_set(n_t, n);
    mpz_sqrt(n_t, n_t);
    k = mpz_sizeinbase(n_t, 2);
    k = ((k - 1) / 8);

    // Dynamically allocating an array of uint8_t
    const uint64_t BUFFER_SIZE = k;
    uint8_t *arr = (uint8_t *) malloc(BUFFER_SIZE * sizeof(uint8_t));
    arr[0] = 0xFF;

    size_t j;
    do {
        j = fread(arr + 1, sizeof(uint8_t), BUFFER_SIZE - 1, infile);
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 0, 0, arr);
        ss_encrypt(cypher, m, n);
        gmp_fprintf(outfile, "%Zx\n", cypher);
    } while (j != 0); // Correct condition to break on?
    mpz_clears(n_t, m, cypher, NULL);
    free(arr);
}

void ss_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t pq) {
    pow_mod(m, c, d, pq);
}

void ss_decrypt_file(FILE *infile, FILE *outfile, mpz_t d, mpz_t pq) {
    uint64_t k;
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    k = mpz_sizeinbase(pq, 2);
    k = ((k - 1) / 8);

    // Dynamically allocating an array
    const uint32_t BUFFER_SIZE = k;
    uint8_t *arr = (uint8_t *) malloc(BUFFER_SIZE * sizeof(uint8_t));
    // uint8_t *buffer = calloc(BUFFER_SIZE, sizeof(uint8_t));
    size_t j;
    do {
        gmp_fscanf(infile, "%Zx\n", c);
        ss_decrypt(m, c, d, pq);
        mpz_export(arr, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(arr + 1, sizeof(uint8_t), j - 1, outfile);
    } while (!feof(infile)); // Correct condition to break on?

    mpz_clears(c, m, NULL);
    free(arr);
}

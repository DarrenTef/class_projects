#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include "randstate.h"
#include "ss.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "b:i:n:d:s:vh"

uint64_t seed_gen(uint64_t seed) {
    srandom(seed);
    seed = random();
    return seed;
}

int main(int argc, char **argv) {
    // struct stat info;
    uint64_t seeding = time(NULL);
    mpz_t p, q, n, pq, d;
    mpz_inits(p, q, n, pq, d, NULL);
    uint64_t nbits = 256;
    uint64_t iters = 50;
    bool v = false;
    bool h = false;
    FILE *pbfile = fopen("ss.pub", "w+");
    FILE *pvfile = fopen("ss.priv", "w+");
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': nbits = (uint64_t) strtoul(optarg, NULL, 10); break;
        case 'i': iters = (uint64_t) strtoul(optarg, NULL, 10); break;
        case 'n':
            fclose(pbfile);
            pbfile = fopen(optarg, "w+");
            break;
        case 'd':
            fclose(pvfile);
            pvfile = fopen(optarg, "w+");
            break;
        case 's': seeding = (uint64_t) strtoul(optarg, NULL, 10); break;
        case 'v': v = true; break;
        case 'h': h = true; break;
        default: h = true;
        }
    }

    if (pbfile == NULL) {
        perror("Error with opening file: pub_keyfile\n");
    }

    if (pvfile == NULL) {
        perror("Error with opening file: pri_keyfile\n");
    }

    uint64_t pv_fd = fileno(pvfile);

    fchmod(pv_fd, S_IRUSR | S_IWUSR);
    // printf("File Descriptor: \t%d\n", pv_fd);	// Used to print the fildes

    randstate_init(seed_gen(seeding));

    ss_make_pub(p, q, n, nbits, iters);
    ss_make_priv(d, pq, p, q);

    char *username = getenv("USER");

    ss_write_pub(n, username, pbfile);
    ss_write_priv(pq, d, pvfile);

    // ss_read_pub(n, username, pbfile);
    // gmp_printf("Name: %s\n%Zu\n", username, n);
    // printf("mode: %08x\n", info.st_mode);	// Used to test if user read-write only

    if (h) {
        printf("SYNOPSIS\n"
               "\tGenerates an SS public/private key par.\n"
               "\n"
               "USAGE\n"
               "\t./keygen [OPTIONS]\n"
               "\n"
               "OPTIONS\n"
               "   -h\t\t\tDisplay program help and usage.\n"
               "   -v\t\t\tDisplay verbose program output.\n"
               "   -b bits\t\tMinimum bits needed for public key n (default: 256).\n"
               "   -i iterations\tMiller-Rabin iterations for testing primes (default: 50).\n"
               "   -n pbfile\t\tPublic key file (default: ss.pub).\n"
               "   -d pvfile\t\tPrivate key file (default: ss.priv).\n"
               "   -s seed\t\tRandom seed for testing.\n");
    } else {
        if (v) {
            gmp_printf("user = %s\n", username);
            gmp_printf("p  (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
            gmp_printf("q  (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
            gmp_printf("n  (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
            gmp_printf("pq (%d bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
            gmp_printf("d  (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
        }
    }

    mpz_clears(n, p, q, pq, d, NULL);
    randstate_clear();
    fclose(pvfile);
    fclose(pbfile);
    return 0;
}

/*
int main(void) {
    mpz_t p, q, d, m, c, e, t_p, t_q, t_n, gcd_v, lcm, n, p_s, pq;
    mpz_inits(p, q, d, m, c, e, t_p, t_q, t_n, gcd_v, lcm, n, p_s, pq, NULL);
    char *p_v = "69074360158192048806239";
    char *q_v = "2394583270958958391426054540310460111182616311";
    char *m_v = "123456789";

    mpz_set_str(p, p_v, 10);
    mpz_set_str(q, q_v, 10);
    mpz_set_str(m, m_v, 10);

    mpz_mul(pq, p, q);
    mpz_mul(n, pq, p);

    mpz_sub_ui(t_p, p, 1);
    mpz_sub_ui(t_q, q, 1);
    mpz_mul(t_n, t_p, t_q);
    mpz_abs(t_n, t_n);
    gcd(gcd_v, t_p, t_q);
    mpz_fdiv_q(lcm, t_n, gcd_v);
    mod_inverse(d, n, lcm);
    pow_mod(c, m, n, n);
    pow_mod(e, c, d, pq);

    gmp_printf("p  (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
    gmp_printf("q  (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
    gmp_printf("n  (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
    gmp_printf("pq  (%d bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
    gmp_printf("lcm  (%d bits) = %Zd\n", mpz_sizeinbase(lcm, 2), lcm);
    gmp_printf("d  (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    gmp_printf("m  (%d bits) = %Zd\n", mpz_sizeinbase(m, 2), m);
    gmp_printf("c  (%d bits) = %Zd\n", mpz_sizeinbase(c, 2), c);
    gmp_printf("e  (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);

    mpz_clears(d, p, q, m, c, e, t_p, t_q, t_n, gcd_v, lcm, n, p_s, pq, NULL);
}
*/

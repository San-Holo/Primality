#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int premiers(mpz_t x, mpz_t y){
	mpz_t a; mpz_init(a);
  mpz_t r; mpz_init(r);
	mpz_t b; mpz_init(b);
	mpz_set(a,x); mpz_set(b,y);
  while (mpz_cmp_ui(b,0)>0) {
    mpz_mod(r,a,b);
    mpz_set(a,b);
    mpz_set(b,r);
  }
  if(mpz_cmp_ui(a,1)==0){
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]){

	mpz_t n; //Le nombre à tester à passer en argument sur la ligne de commande
	int k;

	mpz_t tmp1; //pour calculer les puissances de a
	mpz_init(tmp1);

	mpz_t a; mpz_init(a);
	mpz_t t; mpz_init(t);
	mpz_t max; mpz_init(max);

	gmp_randstate_t state;
	gmp_randinit_mt(state);

	if(argc != 3){
		printf("Le ou les argument(s) fourni(s) n'est/ne sont pas valides\n\n");
	}else{

		mpz_init_set_str(n, argv[1], 10);
		mpz_sub_ui(max,n,3);
		k = atoi(argv[2]);

		for(int i = 0; i<k; i++){
			mpz_urandomm(a,state,max);
			mpz_add_ui(a,a,2);

			if(premiers(a,n)==1){
				mpz_sub_ui(t,n,1);
				mpz_powm(a,a,t,n);
				if(mpz_cmp_ui(a,1)!=0){
					printf("Le nombre fourni est composé\n");
					return 0;
				}
			}
		}

	printf("Le nombre est composé avec une probabilité de %0.24f.\n", pow(0.5,k));

	mpz_clear(n);
	mpz_clear(a);
	mpz_clear(t);
	mpz_clear(max);
	return 0;
	}

}

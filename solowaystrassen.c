#include <stdio.h>
#include <assert.h>
#include <gmp.h>
#include <stdlib.h>
#include <math.h>

void jacobi(mpz_t a, mpz_t s, mpz_t j){
  mpz_t m; mpz_t n;
  mpz_init(m); mpz_init(n);
  mpz_set(m,a); mpz_set(n,s);
  mpz_t r; mpz_init(r);
  mpz_set_ui(j,1);

  if(mpz_sgn(m)<0){
    mpz_mul_si(m,m,(-1));
    if(mpz_congruent_ui_p(n,1,4)!=0){
      mpz_mul_si(j,j,(-1));
    }
  }

  while(mpz_cmp_si(m,2)>=0){
    if(mpz_divisible_ui_p(m,2)!=0){
      mpz_divexact_ui(m,m,2);
      if(mpz_congruent_ui_p(n,3,8)!=0 || mpz_congruent_ui_p(n,5,8)!=0){
        mpz_mul_si(j,j,(-1));
      }
    }else{
      if(mpz_congruent_ui_p(n,1,4)==0 && mpz_congruent_ui_p(m,1,4)==0){
        mpz_mul_si(j,j,(-1));
      }
      mpz_mod(r,n,m);
      mpz_set(n,m);
      mpz_set(m,r);
    }
  }

  if(mpz_cmp_si(m,0)==0){
    mpz_set_ui(j,0);
  }

  mpz_clear(m);
  mpz_clear(n);
  mpz_clear(r);
}


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



void solovaystrassen(mpz_t n, int k){
  mpz_t j; mpz_init(j);
  mpz_t p; mpz_init(p);
  mpz_t a; mpz_init(a);
  mpz_t t; mpz_init(t);
  mpz_t max; mpz_init(max);

  mpz_sub_ui(max,n,3);
  int i;
  gmp_randstate_t state;
  gmp_randinit_mt(state);

  for(i=0;i<k;i++){
    mpz_urandomm(a,state,max);
    mpz_add_ui(a,a,2);

    if(premiers(a,n)==1){

      mpz_sub_ui(t,n,1);
      mpz_set(p,t);

      mpz_divexact_ui(p,p,2);

      mpz_powm(p,a,p,n);


      if(mpz_cmp_ui(p,1)!=0 && mpz_cmp(p,t)!=0){
        printf("n composé\n");
        exit(0);
      }

      jacobi(a,n,j);

      mpz_mod(t,j,n);

      if(mpz_cmp(p,t)!=0){
        printf("n composé\n");
        exit(0);
      }
    }
  }
  printf("n composé avec une probabilité de %0.24f\n",pow(0.5,k));

  mpz_clear(j);
  mpz_clear(p);
  mpz_clear(a);
  mpz_clear(t);
  mpz_clear(max);
  gmp_randclear(state);
}


int main(){
  int flag;
  mpz_t n; int k;
  mpz_init(n);
  char inputStr[1024];

  do{
    printf("Enter n>=3 :\n");
    scanf("%1023s" , inputStr);
    flag = mpz_set_str(n,inputStr, 10);
    assert(flag == 0);

    printf("Enter k>0:\n");
    scanf("%d",&k);
  }while(mpz_cmp_si(n,3)<0 || mpz_divisible_ui_p(n,2)!=0 || k<=0);

  printf("-------------------------------------------\n");

  printf ("n = ");
  mpz_out_str(stdout,10,n);
  printf ("\n");

  printf("k = %d\n",k);

  solovaystrassen(n,k);

  mpz_clear(n);

}

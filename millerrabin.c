#include <stdio.h>
#include <assert.h>
#include <gmp.h>
#include <stdlib.h>
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

int decompose(mpz_t t, mpz_t d, int s){

  mpz_set(d,t);
  int find = 0;

	while(find==0){
    if(mpz_even_p(d)!=0){
      mpz_divexact_ui(d,d,2);
      s = s*2;
    }else{
      find=1;
    }
  }
  return 0;
}


void millerrabin(mpz_t n, int k){
  mpz_t d; mpz_init(d);
  mpz_t x; mpz_init(x);
  mpz_t a; mpz_init(a);
  mpz_t t; mpz_init(t);
  mpz_t max; mpz_init(max);

  int i,j,s;
  mpz_sub_ui(max,n,3);
  gmp_randstate_t state;
  gmp_randinit_mt(state);

  for(i=0;i<k;i++){
    s=1;
    mpz_urandomm(a,state,max);
    mpz_add_ui(a,a,2);

    if(premiers(a,n)==1){
      mpz_sub_ui(t,n,1);
      decompose(t,d,s);
      mpz_powm(x,a,d,n);


      if(mpz_cmp_ui(x,1)!=0 && mpz_cmp(x,t)!=0){
        printf("n composé\n");
        exit(0);
      }

      for(j=0;j<s;j++){
        mpz_powm_ui(x,x,2,n);
        if(mpz_cmp_ui(x,1)!=0){
          printf("n composé\n");
          exit(0);
        }
      }
    }
  }

  printf("n composé avec une probabilité de %0.36f\n",pow(0.25,k));
  mpz_clear(x);
  mpz_clear(a);
  mpz_clear(d);
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

  millerrabin(n,k);

  mpz_clear(n);

}

#include <stdio.h>
#include <assert.h>
#include <gmp.h>



void jacobi(mpz_t m, mpz_t n, mpz_t s){
  mpz_t r; mpz_init(r);
  mpz_set_ui(s,1);

  if(mpz_sgn(m)<0){
    mpz_mul_si(m,m,(-1));
    if(mpz_congruent_ui_p(n,1,4)!=0){
      mpz_mul_si(s,s,(-1));
    }
  }

  while(mpz_cmp_si(m,2)>=0){
    if(mpz_divisible_ui_p(m,2)!=0){
      mpz_divexact_ui(m,m,2);
      if(mpz_congruent_ui_p(n,3,8)!=0 || mpz_congruent_ui_p(n,5,8)!=0){
        mpz_mul_si(s,s,(-1));
      }
    }else{
      if(mpz_congruent_ui_p(n,1,4)==0 && mpz_congruent_ui_p(m,1,4)==0){
        mpz_mul_si(s,s,(-1));
      }
      mpz_mod(r,n,m);
      mpz_set(n,m);
      mpz_set(m,r);
    }
  }

  if(mpz_cmp_si(m,0)==0){
    mpz_set_ui(s,0);
  }
}



int main(){
  int flag;
  mpz_t n; mpz_t m; mpz_t s;
  mpz_init(s); mpz_init(n); mpz_init(m);
  char inputStr[1024];

  do{

    printf("Enter m (in Z) :\n");
    scanf("%1023s" , inputStr);
    flag = mpz_set_str(m,inputStr, 10);
    assert(flag == 0);

    printf("Enter n>=3 :\n");
    scanf("%1023s" , inputStr);
    flag = mpz_set_str(n,inputStr, 10);
    assert(flag == 0);

  }while(mpz_cmp_si(n,3)<0 || mpz_divisible_ui_p(n,2)!=0);

  printf("-------------------------------------------\n");
  printf ("m = ");
  mpz_out_str(stdout,10,m);
  printf ("\n");

  printf ("n = ");
  mpz_out_str(stdout,10,n);
  printf ("\n");

  jacobi(m,n,s);

  printf ("s = ");
  mpz_out_str(stdout,10,s);
  printf ("\n");

  mpz_clear(m);
  mpz_clear(n);
  mpz_clear(s);

}

#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
  ({                                                    \
    lambda$_ret lambda$__anon$ lambda$_args             \
      lambda$_body                                      \
      &lambda$__anon$;                                  \
  })

int main()
{
  printf("%f\n",(*lambda(float, (float x), { return x*x; }))(2.0));
  return 0;
}

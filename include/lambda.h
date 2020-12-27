#ifndef LAMBDA_H
#define LAMBDA_H

/* Requires --std=gnu99 */

#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
  ({                                                    \
    lambda$_ret lambda$__anon$ lambda$_args             \
      lambda$_body                                      \
      &lambda$__anon$;                                  \
  })

#endif /* LAMBDA_H */

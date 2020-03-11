long long fib(int n) {
  if (n < 2)
    return n;
  long long result = 0;
  long long f0 = 0;
  long long f1 = 1;
  for (int i = 1; i < n; i++) {
    result = f0 + f1;
    f0 = f1;
    f1 = result;
  }
  return result;
}

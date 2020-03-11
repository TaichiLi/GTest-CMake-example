long long fac(int n) {
  if (n < 2)
    return 1;
  return (long long)(n * fac(n - 1));
}
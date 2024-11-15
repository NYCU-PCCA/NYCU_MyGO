u64 modmul(u64 a, u64 b, u64 M) {
	i64 ret = a * b - M * u64(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= i64(M));
}

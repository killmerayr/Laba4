package main

// Генерация последовательности BBS
func BBSGenerate(count int, p, q, seed int64) []int64 {
	M := p * q
	x := (seed * seed) % M
	sequence := make([]int64, 0, count)
	sequence = append(sequence, x)
	for i := 1; i < count; i++ {
		x = (x * x) % M
		sequence = append(sequence, x)
	}
	return sequence
}

// Быстрое возведение в степень по модулю
func ModPow(base, exp, mod int64) int64 {
	result := int64(1)
	base = base % mod
	for exp > 0 {
		if exp%2 == 1 {
			result = (result * base) % mod
		}
		base = (base * base) % mod
		exp /= 2
	}
	return result
}

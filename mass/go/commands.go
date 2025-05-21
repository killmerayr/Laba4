package main

import (
	"math/rand"
	"sort"
	"time"
	"unicode"
)

// Задание 1: Генерация массива 1 из n четных чисел в диапазоне [100, 900]
func GenerateArray1(n int) []int {
	arr := make([]int, 0, n)
	rnd := rand.New(rand.NewSource(time.Now().UnixNano()))
	for len(arr) < n {
		num := rnd.Intn(801) + 100 // [100, 900]
		if num%2 == 0 {
			arr = append(arr, num)
		}
	}
	return arr
}

// Генерация массива 2 из n/2 чисел в диапазоне [2, 50]
func GenerateArray2(n int) []int {
	arr := make([]int, 0, n/2)
	rnd := rand.New(rand.NewSource(time.Now().UnixNano()))
	for len(arr) < n/2 {
		num := rnd.Intn(49) + 2 // [2, 50]
		arr = append(arr, num)
	}
	return arr
}

// Задание 2: Выбор четных на нечетных местах и нечетных на четных местах
func SelectNum(evenNum, divNum []int) ([]int, []int) {
	evOnNotEv := make([]int, 0)
	for i, num := range evenNum {
		if i%2 != 0 {
			evOnNotEv = append(evOnNotEv, num)
		}
	}
	notEvOnEv := make([]int, 0)
	for i, num := range divNum {
		if i%2 == 0 && num%2 != 0 {
			notEvOnEv = append(notEvOnEv, num)
		}
	}
	return evOnNotEv, notEvOnEv
}

// Задание 3: Массив из k чисел - результат целочисленного деления случайных элементов
func DivMass(evenNum, divNum []int, k int) []int {
	nums := make([]int, 0, k)
	if len(evenNum) == 0 || len(divNum) == 0 || k <= 0 {
		return nums
	}
	rnd := rand.New(rand.NewSource(time.Now().UnixNano()))
	for len(nums) < k {
		a := evenNum[rnd.Intn(len(evenNum))]
		b := divNum[rnd.Intn(len(divNum))]
		if b == 0 {
			continue
		}
		nums = append(nums, a/b)
	}
	return nums
}

// Задание 4: Генерация массива случайных символов
func GenerateSmb(k int) []rune {
	symb := make([]rune, 0, k)
	rnd := rand.New(rand.NewSource(time.Now().UnixNano()))
	for len(symb) < k {
		symbol := rune(rnd.Intn(95) + 32) // [32, 126] печатаемые ASCII
		symb = append(symb, symbol)
	}
	return symb
}

// Удаление заглавных букв из массива символов
func DelCapLet(symbols []rune) []rune {
	result := make([]rune, 0, len(symbols))
	for _, ch := range symbols {
		if !unicode.IsUpper(ch) {
			result = append(result, ch)
		}
	}
	return result
}

// Задание 5: Массив из [0, 300], сортировка, фильтрация по повторяющимся цифрам
func GenerateAndFilterArray(n int) []int {
	arr := make([]int, 0, n)
	rnd := rand.New(rand.NewSource(time.Now().UnixNano()))
	for len(arr) < n {
		arr = append(arr, rnd.Intn(301)) // [0, 300]
	}
	sort.Ints(arr)
	filtered := make([]int, 0)
	for _, num := range arr {
		digits := [10]int{}
		tmp := num
		for tmp > 0 {
			digits[tmp%10]++
			tmp /= 10
		}
		for _, d := range digits {
			if d >= 2 {
				filtered = append(filtered, num)
				break
			}
		}
	}
	return filtered
}

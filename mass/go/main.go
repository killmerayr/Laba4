package main

import (
	"fmt"
)

func main() {
	n := 10 // n должно быть четным
	k := 12 // k >= 10

	// 1. Генерация массивов
	arr1 := GenerateArray1(n)
	arr2 := GenerateArray2(n)

	fmt.Print("Массив 1: ")
	for _, x := range arr1 {
		fmt.Printf("%d ", x)
	}
	fmt.Println()

	fmt.Print("Массив 2: ")
	for _, x := range arr2 {
		fmt.Printf("%d ", x)
	}
	fmt.Println()

	// 2. Четные элементы массива 1 на нечетных местах и нечетные массива 2 на четных местах
	evenOnOdd, oddOnEven := SelectNum(arr1, arr2)
	fmt.Print("Четные элементы массива 1 на нечетных местах: ")
	for _, x := range evenOnOdd {
		fmt.Printf("%d ", x)
	}
	fmt.Println()

	fmt.Print("Нечетные элементы массива 2 на четных местах: ")
	for _, x := range oddOnEven {
		fmt.Printf("%d ", x)
	}
	fmt.Println()

	// 3. Массив из k чисел - результат целочисленного деления случайных элементов
	divArr := DivMass(arr1, arr2, k)
	fmt.Printf("Массив целочисленного деления (k=%d): ", k)
	for _, x := range divArr {
		fmt.Printf("%d ", x)
	}
	fmt.Println()

	// 4. Массив случайных символов и удаление заглавных букв
	symbols := GenerateSmb(k)
	fmt.Print("Массив символов: ")
	for _, c := range symbols {
		fmt.Printf("%c ", c)
	}
	fmt.Println()

	noCaps := DelCapLet(symbols)
	fmt.Print("Без заглавных букв: ")
	for _, c := range noCaps {
		fmt.Printf("%c ", c)
	}
	fmt.Println()

	// 5. Массив из [0, 300], сортировка, фильтрация по повторяющимся цифрам
	filtered := GenerateAndFilterArray(n)
	fmt.Print("Массив с повторяющимися цифрами: ")
	for _, x := range filtered {
		fmt.Printf("%d ", x)
	}
	fmt.Println()
}

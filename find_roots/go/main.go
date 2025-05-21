package main

import (
	"fmt"
	"math"
)

// Графическое отделение корней (поиск интервалов смены знака)
func SeparateRoots(a, b, step float64) [][2]float64 {
	var intervals [][2]float64
	prev := Func(a)
	xPrev := a
	for x := a + step; x <= b; x += step {
		curr := Func(x)
		if prev*curr < 0 {
			intervals = append(intervals, [2]float64{xPrev, x})
		}
		prev = curr
		xPrev = x
	}
	return intervals
}

func main() {
	a, b, step, eps := -2.0, 2.0, 0.01, 1e-4
	maxIter := 2000

	// 1. Графическое отделение корней
	intervals := SeparateRoots(a, b, step)
	fmt.Println("Интервалы смены знака (отделение корней):")
	for _, lr := range intervals {
		fmt.Printf("[%.4f, %.4f]\n", lr[0], lr[1])
	}
	fmt.Println()

	// 2. Метод половинного деления
	fmt.Println("Метод половинного деления:")
	fmt.Printf("%5s%15s%15s%15s%15s\n", "N", "a_n", "b_n", "b_n - a_n", "f(c)")
	for _, lr := range intervals {
		left, right := lr[0], lr[1]
		k := 0
		for (right - left) > eps {
			c := (left + right) / 2
			fc := Func(c)
			fmt.Printf("%5d%15.4f%15.4f%15.4f%15.4f\n", k, left, right, right-left, fc)
			if Func(left)*fc < 0 {
				right = c
			} else {
				left = c
			}
			k++
		}
		fmt.Printf("Корень: %.4f за %d итераций\n\n", (left+right)/2, k)
	}

	// 3. Метод Ньютона
	fmt.Println("Метод Ньютона:")
	fmt.Printf("%5s%20s%20s%20s%20s\n", "N", "x_n", "x_n+1", "|x_n+1 - x_n|", "f(x_n+1)")
	for _, lr := range intervals {
		x := (lr[0] + lr[1]) / 2
		k := 0
		var xNext float64
		for {
			xNext = x - Func(x)/FuncPr(x)
			fmt.Printf("%5d%20.4f%20.4f%20.4f%20.4f\n", k, x, xNext, math.Abs(xNext-x), Func(xNext))
			if math.Abs(Func(xNext)) <= eps || k >= maxIter {
				break
			}
			x = xNext
			k++
		}
		fmt.Printf("Корень: %.4f за %d итераций\n\n", xNext, k)
	}

	// 4. Метод простых итераций (используем только Fi1 для примера)
	fmt.Println("Метод простых итераций:")
	fmt.Printf("%5s%20s%20s%20s%20s\n", "N", "x_n", "x_n+1", "|x_n+1 - x_n|", "f(x_n+1)")
	for _, lr := range intervals {
		x := (lr[0] + lr[1]) / 2
		k := 0
		var xNext float64
		for {
			xNext = Fi1(x)
			fmt.Printf("%5d%20.4f%20.4f%20.4f%20.4f\n", k, x, xNext, math.Abs(xNext-x), Func(xNext))
			if math.IsNaN(xNext) || math.IsInf(xNext, 0) {
				fmt.Println("Итерация ушла в область неопределенности!")
				break
			}
			if math.Abs(xNext-x) <= eps || k >= maxIter {
				break
			}
			x = xNext
			k++
		}
		fmt.Printf("Корень: %.4f за %d итераций\n\n", xNext, k)
	}

	// 5. Вывод всех корней (по методу половинного деления)
	fmt.Println("Все найденные корни:")
	for _, lr := range intervals {
		left, right := lr[0], lr[1]
		for (right - left) > eps {
			c := (left + right) / 2
			if Func(left)*Func(c) < 0 {
				right = c
			} else {
				left = c
			}
		}
		fmt.Printf("%.4f\n", (left+right)/2)
	}
}

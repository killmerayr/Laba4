package main

import (
	"errors"
	"math"
)

// x^2 + e^x = 2

func Func(x float64) float64 {
	return x*x + math.Exp(x) - 2
}

func FuncPr(x float64) float64 {
	return 2*x + math.Exp(x)
}
func FuncPr2(x float64) float64 {
	return 2 + math.Exp(x)
}

func Fi1(x float64) float64 {
	return math.Log(2 - x*x)
}
func Fi1Pr(x float64) float64 {
	return -2 * x / (2 - x*x)
}
func Fi2(x float64) float64 {
	return math.Sqrt(2 - math.Exp(x))
}
func Fi2Pr(x float64) float64 {
	return -math.Exp(x) / (2 * math.Sqrt(2-math.Exp(x)))
}

func IsExist(start, end float64) bool {
	return Func(start)*Func(end) < 0
}

func OneRoot(start, end, step float64) bool {
	if !IsExist(start, end) {
		return false
	}
	countPositive, countNegative := 0, 0
	for x := start; x <= end; x += step {
		sg := FuncPr(x)
		if sg > 0 {
			countPositive++
		}
		if sg < 0 {
			countNegative++
		}
	}
	return countPositive == int((end-start)/step)+1 || countNegative == int((end-start)/step)+1
}

func ThRolle(start, end float64) bool {
	return Func(start) == Func(end)
}

func HalfDiv(a, b, eps float64) (float64, int, error) {
	k := 0
	if Func(a)*Func(b) >= 0 {
		return 0, 0, errors.New("Возможно, функция не меняет знака")
	}
	for (b - a) > eps {
		c := (a + b) / 2
		if Func(a)*Func(c) < 0 {
			b = c
		} else {
			a = c
		}
		k++
	}
	return (a + b) / 2, k, nil
}

func Newton(x, eps float64, maxIter int) (float64, int, error) {
	k := 0
	if Func(x)*FuncPr2(x) <= 0 {
		return 0, 0, errors.New("Неверно заданное приближение")
	}
	for math.Abs(Func(x)) > eps && k < maxIter {
		x = x - Func(x)/FuncPr(x)
		k++
	}
	return x, k, nil
}

func MaxDerivative(f func(float64) float64, a, b, step float64) float64 {
	maxVal := 0.0
	for x := a; x <= b; x += step {
		val := math.Abs(f(x))
		if math.IsNaN(val) || math.IsInf(val, 0) {
			return math.Inf(1)
		}
		if val > maxVal {
			maxVal = val
		}
	}
	return maxVal
}

func SimpleIterationAuto(x0, eps float64, maxIter int, a, b, q, step float64) (float64, int, error) {
	type phiFunc struct {
		phi   func(float64) float64
		phiPr func(float64) float64
	}
	phiCandidates := []phiFunc{
		{Fi1, Fi1Pr},
		{Fi2, Fi2Pr},
	}
	var chosenPhi func(float64) float64
	minMax := math.Inf(1)
	for _, cand := range phiCandidates {
		maxDer := MaxDerivative(cand.phiPr, a, b, step)
		if maxDer < q && maxDer < minMax {
			minMax = maxDer
			chosenPhi = cand.phi
		}
	}
	if chosenPhi == nil {
		return 0, 0, errors.New("Нет подходящей fi-функции: условие сходимости не выполняется")
	}
	k := 0
	x1 := x0
	for k < maxIter {
		x1 = chosenPhi(x0)
		if math.IsNaN(x1) || math.IsInf(x1, 0) {
			return 0, k, errors.New("Итерация ушла в область неопределенности!")
		}
		if math.Abs(x1-x0) <= eps {
			break
		}
		x0 = x1
		k++
	}
	return x1, k, nil
}

package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Подсчет очков по правилам
func getScores(a, b bool) (int, int) {
	switch {
	case a && b:
		return 24, 24
	case !a && !b:
		return 4, 4
	case a && !b:
		return 0, 20
	case !a && b:
		return 20, 0
	default:
		return 0, 0
	}
}

// Функция для запуска игры между двумя алгоритмами
func playGame(
	algoA func(int, []bool, []bool) bool,
	algoB func(int, []bool, []bool) bool,
	nameA, nameB string,
) int {
	rand.Seed(time.Now().UnixNano())
	rounds := rand.Intn(101) + 100 // [100, 200]

	choicesA := make([]bool, 0, rounds)
	choicesB := make([]bool, 0, rounds)
	scoreA, scoreB := 0, 0

	for round := 0; round < rounds; round++ {
		moveA := algoA(round, choicesA, choicesB)
		moveB := algoB(round, choicesB, choicesA)
		choicesA = append(choicesA, moveA)
		choicesB = append(choicesB, moveB)

		pointsA, pointsB := getScores(moveA, moveB)
		scoreA += pointsA
		scoreB += pointsB
	}

	fmt.Printf("Game: %s vs %s | Rounds: %d\n", nameA, nameB, rounds)
	fmt.Printf("%s score: %d\n", nameA, scoreA)
	fmt.Printf("%s score: %d\n", nameB, scoreB)
	fmt.Println("-----------------------------")

	if scoreA > scoreB {
		return 1
	} else if scoreA < scoreB {
		return 2
	}
	return 0
}

func main() {
	// Турнирная сетка: полуфиналы и финал
	// Полуфинал 1: Algo1 vs Algo2
	winner1 := playGame(Algo1, Algo2, "Algo1", "Algo2")

	// Полуфинал 2: победитель полуфинала 1 vs Algo3
	if winner1 == 1 {
		finalWinner := playGame(Algo1, Algo3, "Algo1", "Algo3")
		fmt.Print("Финал: ")
		if finalWinner == 1 {
			fmt.Println("Algo1 победил!")
		} else if finalWinner == 2 {
			fmt.Println("Algo3 победил!")
		} else {
			fmt.Println("Ничья в финале!")
		}
	} else if winner1 == 2 {
		finalWinner := playGame(Algo2, Algo3, "Algo2", "Algo3")
		fmt.Print("Финал: ")
		if finalWinner == 1 {
			fmt.Println("Algo2 победил!")
		} else if finalWinner == 2 {
			fmt.Println("Algo3 победил!")
		} else {
			fmt.Println("Ничья в финале!")
		}
	} else {
		// Если ничья в первом полуфинале, оба проходят в финал
		finalWinner1 := playGame(Algo1, Algo3, "Algo1", "Algo3")
		finalWinner2 := playGame(Algo2, Algo3, "Algo2", "Algo3")
		fmt.Print("Финал 1: ")
		if finalWinner1 == 1 {
			fmt.Println("Algo1 победил!")
		} else if finalWinner1 == 2 {
			fmt.Println("Algo3 победил!")
		} else {
			fmt.Println("Ничья!")
		}
		fmt.Print("Финал 2: ")
		if finalWinner2 == 1 {
			fmt.Println("Algo2 победил!")
		} else if finalWinner2 == 2 {
			fmt.Println("Algo3 победил!")
		} else {
			fmt.Println("Ничья!")
		}
	}
}

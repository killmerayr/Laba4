package main

import (
	"fmt"
)

type Ranking []string

// Метод Борда
func bordaWinner(votes []Ranking, candidates []string) string {
	scores := make(map[string]int)
	n := len(candidates)

	for _, vote := range votes {
		for i, cand := range vote {
			scores[cand] += n - i - 1
		}
	}

	winner := ""
	maxScore := -1
	for name, score := range scores {
		if score > maxScore {
			maxScore = score
			winner = name
		}
	}
	return winner
}

// Метод Кондорсе
func condorcetWinner(votes []Ranking, candidates []string) string {
	pairwiseWins := make(map[string]map[string]int)
	for _, cand := range candidates {
		pairwiseWins[cand] = make(map[string]int)
	}

	// Подсчет побед в попарных сравнениях
	for _, vote := range votes {
		for i, cand1 := range vote {
			for j := 0; j < i; j++ {
				cand2 := vote[j]
				pairwiseWins[cand1][cand2]++
			}
		}
	}

	for _, cand1 := range candidates {
		winsAll := true
		for _, cand2 := range candidates {
			if cand1 == cand2 {
				continue
			}
			c1Wins := pairwiseWins[cand1][cand2]
			c2Wins := pairwiseWins[cand2][cand1]
			if c1Wins <= c2Wins {
				winsAll = false
				break
			}
		}
		if winsAll {
			return cand1
		}
	}
	return "No Condorcet winner"
}

func main() {
	candidates := []string{"Petya", "Vasya", "Olya"}

	votes := []Ranking{
		{"Vasya", "Olya", "Petya"},
		{"Olya", "Vasya", "Petya"},
		{"Vasya", "Petya", "Olya"},
		{"Olya", "Petya", "Vasya"},
		{"Vasya", "Olya", "Petya"},
	}

	borda := bordaWinner(votes, candidates)
	condorcet := condorcetWinner(votes, candidates)

	fmt.Println("Borda winner:", borda)
	fmt.Println("Condorcet winner:", condorcet)

	if borda != condorcet {
		fmt.Println("Методы дали разные результаты. Это возможно из-за различий в логике оценки.")
	}
}

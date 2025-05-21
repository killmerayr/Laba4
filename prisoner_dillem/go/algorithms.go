package main

// Algo1: Всегда предает (остается для теста)
func Algo1(roundNumber int, selfChoices, enemyChoices []bool) bool {
	return false
}

// Algo2: "Зеркальный" — начинает с сотрудничества, потом повторяет ход противника
func Algo2(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber == 0 {
		return true // Первый ход — сотрудничество
	}
	return enemyChoices[roundNumber-1]
}

// Algo3: "Аналитик" — если противник часто предает, начинаем предавать
func Algo3(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber < 3 {
		return true // Первые 3 хода — сотрудничаем
	}
	betrayCount := 0
	for _, move := range enemyChoices {
		if !move {
			betrayCount++
		}
	}
	betrayRate := float64(betrayCount) / float64(roundNumber)
	if betrayRate > 0.6 {
		return false // Если предательств больше 60% — предаем
	}
	return true // Иначе сотрудничаем
}

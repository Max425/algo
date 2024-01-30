package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

var (
	values = map[string]int{"2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "T": 10, "J": 11, "Q": 12, "K": 13, "A": 14}
	suits  = []string{"S", "C", "D", "H"}
)

type Combination int

const (
	Old Combination = iota
	Pair
	Set
)

type Card struct {
	Value string
	Suit  string
}

func (c1 *Card) isLess(c2 *Card) bool {
	return values[c1.Value] < values[c2.Value]
}

func (c1 *Card) isEqual(c2 *Card) bool {
	return values[c1.Value] == values[c2.Value]
}

type Player struct {
	Cards []Card
}

func makeDeck() *map[Card]bool {
	res := make(map[Card]bool)
	for v := range values {
		for _, s := range suits {
			res[Card{v, s}] = true
		}
	}
	return &res
}

func isFirstWin(players *[]Player, card *Card) bool {
	var combination Combination
	var maxCard Card
	for i, player := range *players {
		tmpCombination := Old
		tmpMaxCard := player.Cards[0]
		if player.Cards[0].isEqual(card) && player.Cards[1].isEqual(card) {
			tmpCombination = Set
		} else if player.Cards[0].isEqual(card) || player.Cards[1].isEqual(card) {
			tmpCombination = Pair
			tmpMaxCard = *card
		} else if player.Cards[0].isEqual(&player.Cards[1]) {
			tmpCombination = Pair
		} else if tmpMaxCard.isLess(&player.Cards[1]) || tmpMaxCard.isLess(card) {
			if player.Cards[1].isLess(card) {
				tmpMaxCard = *card
			} else {
				tmpMaxCard = player.Cards[1]
			}
		}
		if i == 0 {
			combination = tmpCombination
			maxCard = tmpMaxCard
		} else if tmpCombination > combination || tmpCombination == combination && maxCard.isLess(&tmpMaxCard) {
			return false
		}
	}
	return true
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)

	deck := makeDeck()

	tmp, _ := in.ReadString('\n')
	n, _ := strconv.Atoi(strings.TrimSpace(tmp))
	for i := 0; i < n; i++ {

		// копируем игральную колоду
		copyDeck := make(map[Card]bool)
		for key, value := range *deck {
			copyDeck[key] = value
		}

		tmp, _ = in.ReadString('\n')
		playersCount, _ := strconv.Atoi(strings.TrimSpace(tmp))

		// заполнение игроков
		var players []Player
		for j := 0; j < playersCount; j++ {
			s, _ := in.ReadString('\n')
			cardsStr := strings.Split(strings.TrimSpace(s), " ")
			var cards []Card

			// карты j-го игрока
			for _, card := range cardsStr {
				newCard := Card{string(card[0]), string(card[1])}
				cards = append(cards, newCard)
				copyDeck[newCard] = false
			}
			players = append(players, Player{cards})
		}

		var win []Card
		for key, value := range copyDeck {
			if value && isFirstWin(&players, &key) {
				win = append(win, key)
			}
		}

		// вывод
		out.WriteString(strconv.Itoa(len(win)) + "\n")
		for _, card := range win {
			out.WriteString(card.Value + card.Suit + "\n")
		}
	}
	out.Flush()
}

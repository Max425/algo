package main

import (
	"log"
	"main/internal/read"
)

func main() {
	counties, err := read.CSV("data/cit.csv", 0)
	if err != nil {
		log.Fatal(err)
	}
	log.Println(len(counties))

	country := "Россия"

	if _, ok := counties[country]; ok {
		log.Println("Country found")
	} else {
		log.Println("Country not found")
	}

	countryRune := []rune(country)
	lastLetter := countryRune[len(countryRune)-1]
	log.Println(string(lastLetter))

	//map[rune - буква]все слова на эту букву
}

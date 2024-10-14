package main

import (
	"database/sql"
	"encoding/csv"
	"fmt"
	_ "github.com/lib/pq" // Импорт драйвера для PostgreSQL
	"log"
	"os"
	"strconv"
)

func main() {
	// Подключаемся к базе данных
	connStr := "host=localhost port=5432 user=postgres password=1474 dbname=postgres sslmode=disable"
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// Открываем файл CSV
	file, err := os.Open("brands_meta.csv.01102024")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// Читаем данные из CSV
	reader := csv.NewReader(file)
	reader.Comma = '|' // Указываем, что разделитель - это |
	records, err := reader.ReadAll()
	if err != nil {
		log.Fatal(err)
	}

	// Пропускаем заголовок
	for _, record := range records[1:] {
		id, _ := strconv.Atoi(record[0])
		name := record[2]
		soldAmount, _ := strconv.Atoi(record[3])
		soldAmountWithStocks, _ := strconv.Atoi(record[4])
		likes, _ := strconv.Atoi(record[5])
		stocksMP, _ := strconv.Atoi(record[6])
		stocksWB, _ := strconv.Atoi(record[7])
		isAdult, _ := strconv.ParseBool(record[8])
		hasBrandZone, _ := strconv.ParseBool(record[9])

		// Выполняем SQL запрос для вставки данных
		query := `
        INSERT INTO meta_tmp1 (id, id_v2, name, sold_amount, sold_amount_with_stocks, likes, stocks_mp, stocks_wb, is_adult, has_brandzone)
        VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10)`
		_, err = db.Exec(query, id, record[1], name, soldAmount, soldAmountWithStocks, likes, stocksMP, stocksWB, isAdult, hasBrandZone)
		if err != nil {
			log.Fatal(err)
		}
	}

	fmt.Println("Данные успешно вставлены!")
}

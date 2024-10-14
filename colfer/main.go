package main

import (
	"fmt"
	"log"
)

func main() {
	// Создаем объект
	person := &Person{Name: "Арсений", Age: 30}

	// Сериализация
	buffer := make([]byte, 1024)
	_ = person.MarshalTo(buffer)

	// Десериализация
	var decodedPerson Person
	_, err := decodedPerson.Unmarshal(buffer)
	if err != nil {
		log.Fatal("Ошибка анмаршалинга:", err)
	}

	fmt.Printf("Декодированный объект: %+v\n", decodedPerson)
}

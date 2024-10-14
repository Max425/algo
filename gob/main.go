package main

import (
	"bytes"
	"encoding/gob"
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	// Создаем объект
	person := Person{Name: "Арсений", Age: 30}

	// Сериализация (кодирование) в бинарный формат
	var buffer bytes.Buffer
	encoder := gob.NewEncoder(&buffer)
	err := encoder.Encode(person)
	if err != nil {
		fmt.Println("Ошибка кодирования:", err)
	}

	// Десериализация (декодирование)
	var decodedPerson Person
	decoder := gob.NewDecoder(&buffer)
	err = decoder.Decode(&decodedPerson)
	if err != nil {
		fmt.Println("Ошибка декодирования:", err)
	}

	fmt.Printf("Декодированный объект: %+v\n", decodedPerson)
}

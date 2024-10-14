package main

import (
	"fmt"
	"github.com/vmihailenco/msgpack/v5"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	// Создаем объект
	person := Person{Name: "Арсений", Age: 30}

	// Сериализация в msgpack
	data, err := msgpack.Marshal(person)
	if err != nil {
		fmt.Println("Ошибка маршалинга:", err)
	}

	// Десериализация из msgpack
	var decodedPerson Person
	err = msgpack.Unmarshal(data, &decodedPerson)
	if err != nil {
		fmt.Println("Ошибка анмаршалинга:", err)
	}

	fmt.Printf("Декодированный объект: %+v\n", decodedPerson)
}

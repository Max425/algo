package main

import (
	"bufio"
	"fmt"
	"os"
)

type Task struct {
	Status string
}

func Check(task Task, commands string) bool {
	if len(commands) < 1 {
		return task.Status == "D"
	}
	command := string(commands[0])
	switch task.Status {
	case "":
		if command == "M" {
			task.Status = command
			return Check(task, commands[1:])
		}
		return false
	case "M":
		if command == "R" || command == "C" || command == "D" {
			task.Status = command
			return Check(task, commands[1:])
		}
		return false
	case "R":
		if command == "C" {
			task.Status = command
			return Check(task, commands[1:])
		}
		return false
	case "C":
		if command == "M" {
			task.Status = command
			return Check(task, commands[1:])
		}
		return false
	case "D":
		if command == "M" {
			task.Status = command
			return Check(task, commands[1:])
		}
		return false
	}

	return false
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testsCount int
	fmt.Fscanln(in, &testsCount)
	for i := 0; i < testsCount; i++ {
		var line string
		fmt.Fscanln(in, &line)
		if Check(Task{""}, line) {
			fmt.Fprintln(out, "YES")
		} else {
			fmt.Fprintln(out, "NO")
		}
	}
}

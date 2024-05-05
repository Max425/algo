package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
	"strings"
)

type Directory struct {
	Dir     string      `json:"dir"`
	Files   []string    `json:"files"`
	Folders []Directory `json:"folders"`
}

func isVirus(file string) bool {
	return len(file) > 5 && file[len(file)-5:] == ".hack"
}

func countInfectedFiles(directory Directory, hasVirus bool) int {
	count := 0
	if hasVirus {
		count += len(directory.Files)
	} else {
		for _, file := range directory.Files {
			if isVirus(file) {
				count += len(directory.Files)
				hasVirus = true
				break
			}
		}
	}
	for _, folder := range directory.Folders {
		count += countInfectedFiles(folder, hasVirus)
	}
	return count
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testsCount int
	fmt.Fscanln(in, &testsCount)
	for i := 0; i < testsCount; i++ {
		var n int
		fmt.Fscanln(in, &n)
		jsonInput := make([]string, 0, n)
		for j := 0; j < n; j++ {
			line, _ := in.ReadString('\n')
			jsonInput = append(jsonInput, line)
		}

		var root Directory
		json.Unmarshal([]byte(strings.Join(jsonInput, "")), &root)
		fmt.Println(countInfectedFiles(root, false))
	}
}

package read

import (
	"encoding/csv"
	"os"
)

func CSV(path string, column int) (map[string]struct{}, error) {
	f, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	reader := csv.NewReader(f)

	records, err := reader.ReadAll()
	if err != nil {
		return nil, err
	}

	data := make(map[string]struct{})
	for _, record := range records {
		data[record[column]] = struct{}{}
	}
	return data, nil
}

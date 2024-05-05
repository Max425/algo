package main

import (
	"encoding/json"
	"fmt"
	"time"
)

type Record struct {
	Query               string `json:"Query"`
	NormQuery           string `json:"NormQuery"`
	Miner               string `json:"Miner"`
	MinerArgs           string `json:"MinerArgs"`
	SortArgs            string `json:"SortArgs"`
	ShardKey            string `json:"ShardKey"`
	ShardQuery          string `json:"ShardQuery"`
	PresetArgs          string `json:"PresetArgs"`
	Status              string `json:"Status"`
	ABGroup             string `json:"ABGroup"`
	ABKey               string `json:"ABKey"`
	ABLabel             string `json:"ABLabel"`
	MasterShardKey      string `json:"MasterShardKey"`
	MasterShardQuery    string `json:"MasterShardQuery"`
	MetaInfo            string `json:"MetaInfo"`
	ShardQuery2         string `json:"ShardQuery2"`
	SearchFilter        string `json:"SearchFilter"`
	DefaultSearchFilter struct {
		Filter string `json:"Filter"`
		Ver    int    `json:"Ver"`
	} `json:"DefaultSearchFilter"`
	UseShardQuery int      `json:"UseShardQuery"`
	Version       int      `json:"Version"`
	QueryAnalysis string   `json:"QueryAnalysis"`
	Embedding     []string `json:"Embedding"`
	PresetConfig  *string  `json:"PresetConfig"`
	PresetFilter  *string  `json:"PresetFilter"`
	Promo         bool     `json:"Promo"`
	Delete        bool     `json:"Delete"`
	DeleteQueue   bool     `json:"DeleteQueue"`
	FromQueue     bool     `json:"FromQueue"`
	NotMining     bool     `json:"NotMining"`
	PushExact     bool     `json:"PushExact"`
}

type Data struct {
	Author string    `json:"author"`
	Rv     time.Time `json:"rv"`
}

func main() {
	jsonData := `{
        "Record": {
            "Query": "литературный клуб",
            "NormQuery": "subj_клуб литературный",
            "Miner": "context;context-v2",
            "MinerArgs": "--context-subject=\"книги\" --max-product=35000 --query=\"литературный клуб\" --context-subject-filter=true --use-hash-tokens=true;--context-subject=\"книги\" --max-product=35000 --query=\"литературный клуб\" --context-subject-filter=true --use-hash-tokens=true",
            "SortArgs": "",
            "ShardKey": "presets/bucket_653",
            "ShardQuery": "preset=18922401",
            "PresetArgs": "",
            "Status": "ok",
            "ABGroup": "",
            "ABKey": "",
            "ABLabel": "",
            "MasterShardKey": "",
            "MasterShardQuery": "",
            "MetaInfo": "",
            "ShardQuery2": "",
            "SearchFilter": "",
            "DefaultSearchFilter": {
                "Filter": "",
                "Ver": 0
            },
            "UseShardQuery": 0,
            "Version": 2,
            "QueryAnalysis": "",
            "Embedding": [],
            "PresetConfig": null,
            "PresetFilter": null,
            "Promo": false,
            "Delete": false,
            "DeleteQueue": false,
            "FromQueue": false,
            "NotMining": false,
            "PushExact": false
        },
        "author": "gubeydullin.i",
        "rv": "2024-02-27T18:02:39+03:00"
    }`

	var data Data
	err := json.Unmarshal([]byte(jsonData), &data)
	if err != nil {
		fmt.Println("Ошибка при разборе JSON:", err)
		return
	}

	// Вывод данных из объекта
	fmt.Println("Author:", data.Author)
	fmt.Println("Rv:", data.Rv)
}

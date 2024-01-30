package main

import (
	"bufio"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Comment struct {
	ID, ParentID int
	Message      string
	Child        []*Comment
}

func PrintTree(root *Comment, out *bufio.Writer, level int, lastChild bool) {
	for i := 0; i < level; i++ {
		if lastChild {
			out.WriteString(" ")
		} else {
			out.WriteString("|")
		}
		if i+1 < level {
			out.WriteString("  ")
		}
	}
	if level > 0 {
		out.WriteString("|--")
	}
	out.WriteString(root.Message + "\n")
	sort.Slice(root.Child, func(i, j int) bool {
		return root.Child[i].ID < root.Child[j].ID
	})
	for i, node := range root.Child {
		PrintTree(node, out, level+1, i == len(root.Child)-1)
	}
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)

	tmp, _ := in.ReadString('\n')
	testsCount, _ := strconv.Atoi(strings.TrimSpace(tmp))

	for i := 0; i < testsCount; i++ {
		var comments []*Comment
		commentMap := make(map[int]*Comment)

		tmp, _ = in.ReadString('\n')
		counts, _ := strconv.Atoi(strings.TrimSpace(tmp))
		for j := 0; j < counts; j++ {
			tmp, _ = in.ReadString('\n')
			line := strings.Split(strings.TrimSpace(tmp), " ")
			id, _ := strconv.Atoi(line[0])
			ParentId, _ := strconv.Atoi(line[1])
			c := &Comment{id, ParentId, strings.TrimSpace(strings.Join(line[2:], " ")), []*Comment{}}
			comments = append(comments, c)
			commentMap[id] = c
		}
		var root []*Comment
		for _, comment := range comments {
			if comment.ParentID == -1 {
				root = append(root, comment)
			} else {
				commentMap[comment.ParentID].Child = append(commentMap[comment.ParentID].Child, comment)
			}
		}
		for inx, node := range root {
			PrintTree(node, out, 0, inx == len(root)-1)
			out.WriteString("\n")
		}
	}
	out.Flush()
}

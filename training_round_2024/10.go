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

func PrintTree(root *Comment, out *bufio.Writer, delim []string, last bool) {
	for i, sep := range delim {
		out.WriteString(sep)
		if i < len(delim)-1 {
			out.WriteString("  ")
		}
	}
	if len(delim) > 0 {
		out.WriteString("\n")
	}
	for i, sep := range delim {
		out.WriteString(sep)
		if i < len(delim)-1 {
			out.WriteString("  ")
		}
	}

	if len(delim) > 0 {
		out.WriteString("--")
	}
	out.WriteString(root.Message + "\n")

	sort.Slice(root.Child, func(i, j int) bool {
		return root.Child[i].ID < root.Child[j].ID
	})
	if last {
		delim[len(delim)-1] = " "
	}
	delim = append(delim, "|")

	for i, node := range root.Child {
		PrintTree(node, out, delim, i == len(root.Child)-1)
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
			tmp = tmp[:len(tmp)-1]
			line := strings.Split(tmp, " ")
			id, _ := strconv.Atoi(line[0])
			ParentId, _ := strconv.Atoi(line[1])
			c := &Comment{id, ParentId, strings.Join(line[2:], " "), []*Comment{}}
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
		sort.Slice(root, func(i, j int) bool {
			return root[i].ID < root[j].ID
		})
		var delim []string
		for _, node := range root {
			PrintTree(node, out, delim, false)
			out.WriteString("\n")
		}
	}
	out.Flush()
}

package main

import "fmt"

// TreeNode definition for a  tree node.
type TreeNode struct {
	Val    int
	Parent *TreeNode
}

func main() {
	node1 := &TreeNode{1, nil}
	node2 := &TreeNode{2, node1}
	nodeC := &TreeNode{3, node2}
	nodeB := &TreeNode{4, nodeC}
	node5 := &TreeNode{5, nodeC}
	node6 := &TreeNode{6, node5}
	nodeA := &TreeNode{7, node6}

	fmt.Println(findLowestCommonAncestor(nodeA, nodeB).Val)
}

// LSA
func findLowestCommonAncestor(firstNode, secondNode *TreeNode) *TreeNode {
	for firstNode != nil {
		secondNodeTmp := secondNode
		for secondNodeTmp != nil {
			if firstNode.Val == secondNodeTmp.Val {
				return firstNode
			}
			secondNodeTmp = secondNodeTmp.Parent
		}
		firstNode = firstNode.Parent
	}
	return nil
}

package ods;

public class BSTNode<Node extends BSTNode<Node,T>,T extends Comparable<T>>
		extends BinaryTreeNode<Node> {
	/**
	 * Parent node
	 */
	Node parent;
	
	/**
	 * The key stored at this node
	 */
	T x;
	
	public String toString() {
		return "<" + x.toString() + ">";
	}
}
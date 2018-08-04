package suffixtree;

/**
 * Class used to display a general tree.
 *
 * @param <L> Type of edge labels used in the tree
 */
public final class TreeDisplayer<L> {

    /**
     * Displays the tree, starting from the specified
     * node which is most commonly the tree's root.
     *
     * @param node starting node
     * @throws IllegalArgumentException if node is null
     */
    public void show(final Node<L> node) throws IllegalArgumentException {

        if (node == null) {
            throw new IllegalArgumentException("Null node");
        } else {
            System.out.print(node);
            displayChildrenOf(node, " ");
            System.out.println("\n");
        }
    }

    /**
     * Helper method that displays the children of the specified
     * node and is recursively applied to children.
     *
     * @param node   parent node
     * @param prefix string prefixed to each line to which vertical
     *               bars are added when the parent has more children
     *               after the function is applied to the current child
     */
    private void displayChildrenOf(final Node<L> node, final String prefix) {

        assert node != null : "Null node";
        assert prefix != null : "Null string";

        final int totalEdges = node.getEdges().size(); // Total edge count
        int edgeCount = 1; // 'n' in "nth edge to be considered"

        for (final Edge<L> edge : node.getEdges()) {
            // Add spaces as suffix according to edge length
            final String suffix = spaces(edge.toString().length() + 1);
            // Display children of node that edge leads to
            if (edgeCount == 1) {
                // Print first edge at the node's level (Note :: Extra blank space in
                // "  " and "| " placed to adjust based on node's fixed output width)
                System.out.print("" + edge + edge.getTo());
                displayChildrenOf(edge.getTo(), (prefix + (edgeCount == totalEdges ? "  " : "| ") + suffix));
            } else {
                // Print rest of edges below node
                System.out.println("\n" + prefix + "|");
                System.out.print(prefix + (edgeCount == totalEdges ? "└" : "|") + edge + edge.getTo());
                displayChildrenOf(edge.getTo(), (prefix + (edgeCount == totalEdges ? " " : "|") + suffix));
            }
            edgeCount++;
        }
    }

    /**
     * Repeats a single space for a particular number of times
     *
     * @param count number of spaces
     * @return string containing the spaces
     */
    private String spaces(final int count) {

        assert count >= 0 : "Negative count";
        return (count == 0 ? "" : " " + spaces(count - 1));
    }
}

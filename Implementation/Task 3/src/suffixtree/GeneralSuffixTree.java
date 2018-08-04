package suffixtree;

public abstract class GeneralSuffixTree<L> {

    protected Node<L> root = new Node<>(); // Tree's root node
    protected String treeString; // String represented by the suffix tree

    protected TreeDisplayer<L> displayer = new TreeDisplayer<>(); // For tree display
    protected static final char terminator = '#'; // Indicates end of suffixes

    /**
     * Adds the terminator to the specified string and sets
     * uses the result to set the tree's string.
     *
     * @param treeString the string that the tree will represent (excl. terminator)
     */
    public GeneralSuffixTree(final String treeString) {

        if (treeString == null) {
            System.out.println("Since string passed is null, a blank string will be assumed instead.");
            this.treeString = "" + GeneralSuffixTree.terminator;
        } else {
            // If string contains terminator
            if (treeString.contains("" + GeneralSuffixTree.terminator)) {
                System.out.println("The string contains the reserved character " + GeneralSuffixTree.terminator + ", " +
                        "meaning that any tests performed may give incorrect results. The tree will still be created.");
            }
            // Terminator considered a part of the string represented
            this.treeString = treeString + GeneralSuffixTree.terminator;
        }
    }

    /**
     * Checks if a string is a substring of the suffix tree's
     * string by traversing along the characters of the string
     * and checks that the traversal is successful.
     *
     * @param toCheck string to be considered
     * @return true if string is a substring
     * @throws IllegalArgumentException if string is null
     */
    public boolean substring(final String toCheck) throws IllegalArgumentException {

        if (toCheck == null) {
            throw new IllegalArgumentException("Null string");
        } else {
            return !traverse(root, toCheck).isFailedTraversal();
        }
    }

    /**
     * Checks if a string is a suffix of the suffix tree's string by
     * traversing along the characters of the string and checks that
     * the traversal ends at a leaf node. The terminator is added
     * so that traversal ends exactly at the leaf.
     *
     * @param toCheck string to be considered
     * @throws IllegalArgumentException if string is null
     */
    public boolean suffix(final String toCheck) throws IllegalArgumentException {

        if (toCheck == null) {
            throw new IllegalArgumentException("Null string");
        } else {
            final Node<L> endNode = traverse(root, toCheck + GeneralSuffixTree.terminator).node;
            return endNode != null && endNode.isLeaf();
        }
    }

    /**
     * Counts how many times a substring appears in the suffix tree's string.
     * by traversing along the characters of the string and checking whether
     * the traversal ends at a node or edge. The leaves reachable from the
     * node (or the next closest node, if traversal ended at an edge) that the
     * traversal ended at are then counted (incl. node itself if it is a leaf).
     *
     * @param toCheck string to be considered
     * @return number of times the string appears in the tree's string
     * @throws IllegalArgumentException if string is null
     */
    public long count(final String toCheck) throws IllegalArgumentException {

        if (toCheck == null) {
            throw new IllegalArgumentException("Null string");
        } else {
            final TraversalResult<L> result = traverse(root, toCheck);
            final Node<L> endNode = (result.edge == null ? result.node : result.edge.getTo());
            return (endNode == null ? 0 : countLeaves(endNode));
        }
    }

    /**
     * Finds the longest repeated substring
     * in the suffix tree's string.
     *
     * @return longest repeat
     */
    public abstract String longestRepeat();

    /**
     * Finds the longest common substring between a string and the tree's string
     * by considering all suffixes of the specified string, starting from the
     * largest, and checking the traversal depth reached by each suffix, which
     * indicates the longest prefix of the suffix that can be found in the tree's
     * string. The longest of these prefixes is the longest substring.
     *
     * @param toCheck string to be considered
     * @return longest substring
     * @throws IllegalArgumentException if string is null
     */
    public String longestSubstring(final String toCheck) throws IllegalArgumentException {

        if (toCheck == null) {
            throw new IllegalArgumentException("Null string");
        } else {
            String longest = ""; // stores longest so far
            String currSuffix = toCheck; // current suffix

            while (currSuffix.length() != 0) {
                final int depthTest = traverse(root, currSuffix).depth;
                if (depthTest > longest.length()) {
                    longest = currSuffix.substring(0, depthTest);
                }
                currSuffix = currSuffix.substring(1);
            }
            return longest;
        }
    }

    /**
     * Displays the tree.
     */
    public void show() {
        displayer.show(root);
    }

    /**
     * Helper method to iteratively traverse the suffix trie along
     * the characters of the specified string and get the final node.
     *
     * @param start   traversal starting node
     * @param toCheck string to traverse
     * @return result object with a non-null node if string was not exceeded
     */
    protected abstract TraversalResult<L> traverse(final Node<L> start, final String toCheck);

    /**
     * General method used to count the leaves that
     * are descendants of the specified node. If the
     * node itself is a leaf, the leaf count is 1.
     *
     * @param start parent of the leaves
     * @return the number of leaves
     * @throws IllegalArgumentException if node is null
     */
    protected long countLeaves(final Node<L> start) throws IllegalArgumentException {

        if (start == null) {
            throw new IllegalArgumentException("Null node");
        } else if (start.isLeaf()) { // Node is a leaf
            return 1;
        } else { // Count all leaves recursively from current node
            long count = 0;
            for (final Edge<L> edge : start.getEdges()) {
                count += countLeaves(edge.getTo());
            }
            return count;
        }
    }
}

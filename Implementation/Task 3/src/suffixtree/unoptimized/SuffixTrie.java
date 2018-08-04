package suffixtree.unoptimized;

import suffixtree.*;

import java.util.Collection;

public final class SuffixTrie extends GeneralSuffixTree<Character> {

    /**
     * Generates a suffix trie by considering all the suffixes of
     * the specified string individually, starting from the largest,
     * and generating the paths required by each suffix.
     *
     * @param treeStr String to be represented by the suffix trie
     */
    public SuffixTrie(final String treeStr) {

        super(treeStr); // adds terminator to string
        String currSuffix = treeString; // First suffix to add (reduced by 1 char. with each loop)

        // Generate suffix trie
        while (currSuffix.length() > 0) {
            Node<Character> currNode = root; // Start traversal from root
            for (final char ch : currSuffix.toCharArray()) {
                if (currNode.hasEdgeOut(ch)) {
                    currNode = currNode.getEdgeOut(ch).getTo(); // Edge exists; traverse along edge
                } else {
                    currNode = currNode.addEdgeOut(ch).getTo(); // Edge does not exist; add edge
                }
            }
            currSuffix = currSuffix.substring(1); // Get next (shorter) suffix
        }
    }

    /**
     * (Refer to superclass for full description)
     * (Also refer to helper method longestRepeat(Node, String))
     *
     * @return the longest repeated substring in the tree's string
     */
    @Override
    public String longestRepeat() {
        return longestRepeat(root, "");
    }

    /**
     * Helper method to recursively find the longest repeated substring
     * in the suffix trie's string, starting from the specified string.
     *
     * @param toCheck start of check
     * @param accum   accumulated longest repeat up to toCheck
     * @return longest repeated substring
     */
    private String longestRepeat(final Node<Character> toCheck, final String accum) {

        assert toCheck != null : "Null node";
        assert accum != null : "Null string";

        final Collection<Edge<Character>> edges = toCheck.getEdges();
        String deepest = (edges.size() > 1 ? accum : "");
        /* Deepest assumed to be string up to toCheck if more than 1 child.
        Otherwise, not a substring, so deepest simply considered to be "" */

        // Search for a longer string by traversing the edges (depth first)
        for (final Edge<Character> edge : edges) {
            final String test = longestRepeat(edge.getTo(), accum + edge.getLabel());
            if (test.length() > deepest.length()) {
                deepest = test; // deeper-reaching string
            }
        }
        return deepest;
    }

    /**
     * (Refer to superclass for full description)
     *
     * @throws IllegalArgumentException if node or string is null
     */
    @Override
    protected TraversalResult<Character> traverse(final Node<Character> start, final String toCheck) throws IllegalArgumentException {

        if (start == null) {
            throw new IllegalArgumentException("Null node");
        } else if (toCheck == null) {
            throw new IllegalArgumentException("Null string");
        } else {
            Node<Character> node = start;
            int depthReached = 0;

            // For each character, moves to a new node
            for (final char c : toCheck.toCharArray()) {
                if (node.hasEdgeOut(c)) {
                    node = node.getEdgeOut(c).getTo();
                    depthReached++;
                } else {
                    return new TraversalResult<>(depthReached); // Final node not reached
                }
            }
            return new TraversalResult<>(depthReached, node); // Final node reached
        }
    }
}

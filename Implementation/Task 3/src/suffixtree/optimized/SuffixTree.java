package suffixtree.optimized;

import suffixtree.*;

import java.util.Collection;

public final class SuffixTree extends GeneralSuffixTree<OffLenPair> {

    /**
     * Generates a suffix tree by considering all the suffixes of
     * the specified string individually, starting from the smallest,
     * and generating the paths required by each suffix, changing
     * existing labels as required to suite new suffixes.
     *
     * @param treeStr String to be represented by the suffix trie
     */
    public SuffixTree(final String treeStr) {

        super(treeStr); // adds terminator to string

        // Generate suffix tree
        String currSuffix = "";
        for (int i = treeString.length() - 1; i >= 0; i--) {
            currSuffix = treeString.charAt(i) + currSuffix; // Next suffix
            generatePath(root, currSuffix, i); // Generate path for suffix starting at i
        }
    }

    /**
     * Generates a path starting from the specified node for
     * the specified suffix, which is a suffix of the tree's
     * string starting at character specified by the charIndex.
     *
     * @param currNode the node to start from
     * @param currSuffix the suffix to generate a path for
     * @param charIndex the index at which the suffix starts w.r.t. tree's string
     */
    private void generatePath(final Node<OffLenPair> currNode, final String currSuffix, final int charIndex) {

        assert currNode != null : "Null node";
        assert currSuffix != null : "Null suffix";
        assert !currSuffix.isEmpty() : "Empty suffix"; // must at least contain terminator
        assert charIndex >= 0 && charIndex < treeString.length() : "Invalid index";

        final Edge<OffLenPair> edge = getEdgeOut(currNode, currSuffix.charAt(0));
        if (edge == null) {
            // No edge, so add rest of suffix at one go
            currNode.addEdgeOut(new OffLenPair(charIndex, currSuffix.length()));
        } else {
            // Edge exists, so split according to longest common prefix
            final OffLenPair label = edge.getLabel();
            final int common = longestCommonPrefixLen(currSuffix, label);
            if (common < label.length) {
                // If label is not a prefix of currSuffix, add its remainder along a new edge
                edge.getTo().addEdgeOut(new OffLenPair(label.offset + common, label.length - common));
            }
            // Add remainder of the current suffix recursively along next edge
            generatePath(edge.getTo(), currSuffix.substring(common), charIndex + common);
            // Replace label with
            currNode.replaceEdge(label, new OffLenPair(charIndex, common));
        }
    }

    /**
     * (Refer to superclass for full description)
     * (Also refer to helper method longestRepeat(Node, String))
     * Offset-Length pair is obtained from the helper method which
     * is used to come up with the longest repeat by taking the
     * substring of the tree's string based on the pair's values.
     *
     * @return the longest repeated substring in the tree's string
     */
    @Override
    public String longestRepeat() {

        // Get label representing longest string
        final OffLenPair offLen = longestRepeat(root, OffLenPair.newBlank());
        return treeString.substring(offLen.offset, offLen.total());
    }

    /**
     * Helper method to recursively find the longest repeated substring
     * in the suffix trie's string, starting from the specified string.
     *
     * @param toCheck start of check
     * @param accum   accumulated longest repeat up to toCheck
     * @return longest repeated substring
     */
    private OffLenPair longestRepeat(final Node<OffLenPair> toCheck, final OffLenPair accum) {

        assert toCheck != null : "Null node";
        assert accum != null : "Null string";

        final Collection<Edge<OffLenPair>> edges = toCheck.getEdges();
        OffLenPair deepest = (edges.size() > 1 ? accum : OffLenPair.newBlank());
        /* Deepest assumed to be string up to toCheck if more than 1 child.
        Otherwise, not a substring, so deepest simply considered to be ""
        which is represented by a blank offset-length pair. */

        // Search for a longer string by traversing the edges (depth first)
        for (final Edge<OffLenPair> edge : edges) {
            final OffLenPair test = longestRepeat(edge.getTo(),
                    new OffLenPair(edge.getLabel().offset - accum.length, edge.getLabel().length + accum.length));
            if (test.length > deepest.length) {
                deepest = test; // deeper-reaching traversal
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
    protected TraversalResult<OffLenPair> traverse(final Node<OffLenPair> start, final String toCheck) {

        if (start == null) {
            throw new IllegalArgumentException("Null node");
        } else if (toCheck == null) {
            throw new IllegalArgumentException("Null string");
        } else {
            return this.traverse(start, toCheck, 0);
        }
    }

    /**
     * Method overload which has an extra parameter to
     * keep track of the depth reached by recursion.
     */
    private TraversalResult<OffLenPair> traverse(final Node<OffLenPair> start, final String toCheck, final int depthReached) {

        assert start != null : "Null node";
        assert toCheck != null : "Null string";
        assert depthReached >= 0 : "Negative depth";

        if (toCheck.length() == 0) {
            return new TraversalResult<>(depthReached, start); // String and final edge label both exhausted
        } else {

            // String not exhausted yet
            final Edge<OffLenPair> edge = getEdgeOut(start, toCheck.charAt(0));
            if (edge == null) {
                return new TraversalResult<>(depthReached); // No suitable edge; traversal failed
            } else {

                // Try to exhaust either string or edge label
                final OffLenPair label = edge.getLabel();
                final int common = longestCommonPrefixLen(toCheck, label);
                final int newDepth = depthReached + common;
                if (common == label.length) {
                    // Label exhausted; move to next node
                    return traverse(edge.getTo(), toCheck.substring(common), newDepth);
                } else if (common == toCheck.length()) {
                    // String exhausted but label not exhausted; end at current edge
                    return new TraversalResult<>(newDepth, edge);
                } else {
                    // Neither exhausted; traversal failed
                    return new TraversalResult<>(newDepth);
                }
            }
        }
    }

    /**
     * Given a node and a character, this method searches for an edge
     * representing a string that *starts* with the specified character.
     *
     * @param node node having outward edges to be considered
     * @param toCheck character to be considered
     * @return edge starting with specified character, if it exists; otherwise null
     */
    private Edge<OffLenPair> getEdgeOut(final Node<OffLenPair> node, final char toCheck) {

        assert (node != null) : "Null node";

        for (final Edge<OffLenPair> edge : node.getEdges()) {
            if (treeString.charAt(edge.getLabel().offset) == toCheck) {
                return edge;
            }
        }
        return null;
    }

    /**
     * Calculates the length of the longest common prefix between
     * two strings (the second of which is represented on an offset-
     * length pair based on the tree's string).
     *
     * @param s1 first string
     * @param pair representation of second string
     * @return length of longest common prefix
     */
    private int longestCommonPrefixLen(final String s1, final OffLenPair pair) {

        assert s1 != null : "Null string";
        assert pair != null : "Null pair";
        assert (pair.offset >= 0 && pair.total() <= treeString.length()) : "Invalid pair";

        final String s2 = treeString.substring(pair.offset, pair.total());
        final int shortestLength = Math.min(s1.length(), s2.length());
        for (int i = 0; i < shortestLength; i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                return i; // first index where characters do not match
            }
        }
        return shortestLength; // a whole string is the prefix of the other
    }
}

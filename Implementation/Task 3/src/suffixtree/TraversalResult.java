package suffixtree;

/**
 * Collection of information which described the result
 * of a particular traversal. Since a successful traversal
 * ends either at a node, or midway across an edge, either
 * the node or the edge has to be null.
 *
 * @param <L> Type of edge labels used in the tree
 */
public final class TraversalResult<L> {

    public final Node<L> node; // Node at which traversal ended
    public final Edge<L> edge; // Edge at which traversal ended
    public final int depth; // Depth achieved in the traversal

    /**
     * Successful traversal ended at a node.
     *
     * @param depth depth achieved in the traversal
     * @param node  node at which traversal ended
     */
    public TraversalResult(final int depth, final Node<L> node) {
        this(depth, node, null);
    }

    /**
     * Successful traversal ended mid-way across an edge.
     *
     * @param depth depth achieved in the traversal
     * @param edge  edge at which traversal ended
     */
    public TraversalResult(final int depth, final Edge<L> edge) {
        this(depth, null, edge);
    }

    /**
     * Failed traversal (either no edges found from a particular
     * node or stuck midway across an edge with a non-empty string).
     *
     * @param depth depth achieved in the traversal
     */
    public TraversalResult(final int depth) {
        this(depth, null, null);
    }

    /**
     * General constructor. This is private so that the rule that
     * either the node or edge (or both) must be null is maintained.
     *
     * @param depth depth achieved in the traversal
     * @param node  node at which traversal ended
     * @param edge  edge at which traversal ended
     * @throws IllegalArgumentException if both node and edge are not
     *                                  null or if depth is negative
     */
    private TraversalResult(final int depth, final Node<L> node, final Edge<L> edge) throws IllegalArgumentException {

        if (node != null && edge != null) {
            throw new IllegalArgumentException("Edge and node were both not null");
        } else if (depth < 0) {
            throw new IllegalArgumentException("Depth was negative");
        } else {
            this.node = node;
            this.edge = edge;
            this.depth = depth;
        }
    }

    /**
     * Returns true if the traversal failed
     */
    public boolean isFailedTraversal() {
        return node == null && edge == null;
    }
}
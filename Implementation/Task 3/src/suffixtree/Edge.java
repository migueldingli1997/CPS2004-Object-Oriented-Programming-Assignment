package suffixtree;

/**
 * General edge usable for any tree consisting of
 * nodes that have from zero to multiple children.
 *
 * @param <L> Type of edge labels used in the tree
 */
public class Edge<L> {

    private L label; // Edge label (modifiable)
    private final Node<L> to; // Node that edge leads to

    /**
     * Creates an edge with the specified label. Also assigns
     * a node to the edge so that it points somewhere.
     *
     * @param label edge label
     * @throws IllegalArgumentException if label is null
     */
    Edge(final L label) throws IllegalArgumentException {

        if (label == null) {
            throw new IllegalArgumentException("Null label");
        } else {
            this.to = new Node<>(); // Forced to lead to new node (i.e. never null)
            this.label = label;
        }
    }

    /**
     * Returns the edge's label
     */
    public L getLabel() {
        return label;
    }

    /**
     * Returns the node that the edge leads to
     */
    public Node<L> getTo() {
        return to;
    }

    /**
     * Changes the edge's label.
     *
     * @param label new label
     * @throws IllegalArgumentException if label is null
     */
    void setLabel(final L label) throws IllegalArgumentException {

        if (label == null) {
            throw new IllegalArgumentException("Null label");
        } else {
            this.label = label;
        }
    }

    /**
     * Returns "-label->"
     */
    @Override
    public String toString() {
        return "-" + label + "->";
    }
}

package suffixtree;

import suffixtree.exceptions.*;

import java.util.HashMap;
import java.util.Collection;
import java.util.Map;

/**
 * General node usable for any tree consisting of
 * nodes that have from zero to multiple children.
 *
 * @param <L> Type of edge labels used in the tree
 */
public class Node<L> {

    // Maps edge labels onto the edges themselves
    private Map<L, Edge<L>> edges = new HashMap<>();

    /**
     * Checks whether the node has an outgoing edge
     * having the specified edge label.
     *
     * @param edgeLabel the label to search for
     * @return true if edge does not exist
     * @throws IllegalArgumentException if label is null
     */
    public boolean hasEdgeOut(final L edgeLabel) throws IllegalArgumentException {

        if (edgeLabel == null) {
            throw new IllegalArgumentException("Null label");
        } else {
            return edges.containsKey(edgeLabel);
        }
    }

    /**
     * Adds an outgoing edge to the node with the specified label.
     * Upon creation, the edge automatically leads to a new node.
     *
     * @param edgeLabel the new outgoing edge's label
     * @return the new outgoing edge
     * @throws EdgeOutAlreadyExistsException if edge with the same label already exists
     * @throws IllegalArgumentException      if label is null
     */
    public Edge<L> addEdgeOut(final L edgeLabel) throws EdgeOutAlreadyExistsException, IllegalArgumentException {

        if (edgeLabel == null) {
            throw new IllegalArgumentException("Null label");
        } else if (hasEdgeOut(edgeLabel)) { // Avoided by using !hasEdgeOut before calling method
            throw new EdgeOutAlreadyExistsException("Node already had edge out for " + edgeLabel);
        } else {
            final Edge<L> newEdge = new Edge<>(edgeLabel);
            edges.put(edgeLabel, newEdge);
            return newEdge;
        }
    }

    /**
     * Gets the outgoing edge with the specified label if it exists.
     *
     * @param edgeLabel label of edge to find
     * @return the outgoing edge
     * @throws NoEdgeOutException       if edge with the specified label does not exist
     * @throws IllegalArgumentException if label is null
     */
    public Edge<L> getEdgeOut(final L edgeLabel) throws NoEdgeOutException, IllegalArgumentException {

        if (edgeLabel == null) {
            throw new IllegalArgumentException("Null label");
        } else if (!hasEdgeOut(edgeLabel)) { // Avoided by using hasEdgeOut before calling method
            throw new NoEdgeOutException("Node did not have edge out for " + edgeLabel);
        } else {
            return edges.get(edgeLabel); // Edge exists
        }
    }

    /**
     * Returns true if the node has no outward edges
     */
    public boolean isLeaf() {
        return edges.isEmpty();
    }

    /**
     * Returns the collection of values in the map
     */
    public Collection<Edge<L>> getEdges() {
        return edges.values();
    }

    /**
     * Replaces an outward edge with another edge and connects the
     * old outward edge's node to the new edge. It essentially removes
     * the map entry and recreates it with a new key (the new label)
     * and the same value (the edge) but with a changed label.
     *
     * @param oldLabel label of edge to be replaced
     * @param newLabel label of new edge
     * @throws EdgeOutAlreadyExistsException if edge with the same label already exists
     * @throws NoEdgeOutException            if edge with the specified old label does not exist
     * @throws IllegalArgumentException      if a label is null
     */
    public void replaceEdge(final L oldLabel, final L newLabel) throws EdgeOutAlreadyExistsException,
            NoEdgeOutException, IllegalArgumentException {

        if (oldLabel == null || newLabel == null) {
            throw new IllegalArgumentException("Null label");
        } else if (!hasEdgeOut(oldLabel)) { // Avoided by using hasEdgeOut before calling method
            throw new NoEdgeOutException("Node did not have edge out for " + oldLabel);
        } else if (hasEdgeOut(newLabel)) { // Avoided by using !hasEdgeOut before calling method
            throw new EdgeOutAlreadyExistsException("Node already had edge out for " + newLabel);
        } else {
            final Edge<L> oldEdge = edges.remove(oldLabel);
            edges.put(newLabel, oldEdge); // Set key
            oldEdge.setLabel(newLabel); // Set value
        }
    }

    /**
     * Returns "( )"
     */
    @Override
    public String toString() {
        return "( )";
    }
}

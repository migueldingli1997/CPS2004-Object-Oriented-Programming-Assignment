package suffixtree.exceptions;

/**
 * Thrown in cases where a node does not have a particular outward edge
 * but an attempt is made to obtain an edge with the edge's label.
 */
public final class NoEdgeOutException extends RuntimeException {

    public NoEdgeOutException(final String message) {
        super(message);
    }
}

package suffixtree.exceptions;

/**
 * Thrown in cases where a node already has a particular outward
 * edge but an attempt is made to add a new identical edge.
 */
public class EdgeOutAlreadyExistsException extends RuntimeException {

    public EdgeOutAlreadyExistsException(String message) {
        super(message);
    }
}

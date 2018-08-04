package suffixtree.optimized;

/**
 * Used as the label type for Suffix Trees, where it represents a string
 * by keeping the index of the first character (offset) and length. This
 * class may also be used to store offset-length pairs for other purposes.
 */
final class OffLenPair {

    final int offset; // Index of first character
    final int length; // Number of characters from offset

    OffLenPair(final int offset, final int length) {
        this.offset = offset;
        this.length = length;
    }

    /**
     * Creates an instance which represents empty string by using a zero length.
     *
     * @return the created instance
     */
    static OffLenPair newBlank() {
        return new OffLenPair(0, 0);
    }

    /**
     * Computes the sum of offset and length, which essentially results in
     * the index right after the final character of the represented string.
     *
     * @return the sum
     */
    int total() {
        return offset + length;
    }

    /**
     * Returns "(offset, length)"
     */
    @Override
    public String toString() {
        return "(" + offset + ", " + length + ")";
    }
}

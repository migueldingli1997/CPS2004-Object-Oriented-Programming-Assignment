import suffixtree.optimized.*;
import suffixtree.unoptimized.*;
import suffixtree.*;

import java.util.Scanner;

public class Tester {

    // Strings for test 5
    private final static String t5_thousand_longRepeat = "fM7xBmeAhfwPxLNJKFZDvN9tngjgtZ54oSN9JDim42ONFxDtY2wAHtzKxA9h1KlzGlfTLqq6CkTLxFbsC2KfGeBB8ODgv7wnl3MV";
    private final static String t5_thousand = "8W68QV78nVWfrVIrI7KmqqJ8q3iyX57I5HkoH347MBRjPr8nSS1" + t5_thousand_longRepeat + "M2m5i7P9teaezu9DmDaubtTcUjR1GJJk22vzLquDsOK9rvGoN7R0cJYhCo50bHHW0P7xmYNDgeS0AIRNFSb1kWtN8Au9XZtAQ9kv4JqtArKRx0RtisLDe7QWfOoFMjtTzXCiVwJNM9KGtJjr4ARLF0msBMtJLaKsn13QpK1XvmcVBQBPCGPgvigqZ0lBZ7a5lIqBusm1ynZpM5DbtqEN7a1AtognUgQhG0IDEuGLKKc7V4WtA7UHuxDRxjbgoVtyufG4zGixgZUsRsOVzmFAzBmDYJLu7armosVTgupxrN7gg5gnhoXmvh9y5BS1akEIfSGkjpXEmbEQII9vSKjlbjg2lm7VtYQ0mj3ArxHYG7vibNBM61gRRlGGhecSjabxG6FMmL3hsU0FG9sjtpxYyIFWcCuSWYYojl5wLrmCIaIWYYKmLjbAMhB7rOMbUV1vcwIgZenGTTFaJTfLKGMUCXIxMBQPCLeIZrnxPIMiOThEJz4rMUGes9bZW89XPni0CmP93o71wbfEpRnlOKIkxEjjTjVNsXgaji3lL2vb22aIc7uSaayMWplM8ZlyKHD2qTKlF3x1e5lGR9XYND8I5hfxNjKVnSYSj2ZnzMvGCSOtnMVtoyab79Fjg5AeP9Rcre0LOCioA" + t5_thousand_longRepeat + "IGCmoqxXIxXwa5kHHo8ZvT0DZLNFmejNKnLRnru1hUuLnaTi6KlwlAm1CAahiDJe8QqkZwX6eHTZ0h9eFIDSkLPOutL4AHMIpHgf";

    // General test descriptor
    private static String testDetails = "";

    public static void main(String[] args) {

        Tester tester = new Tester();
        Scanner sc = new Scanner(System.in);

        System.out.println("Press ENTER to perform the five Trie tests...");
        sc.nextLine();

        testDetails = "Trie";
        System.out.println("Starting Test 1...");
        tester.test1(new SuffixTrie(""));
        System.out.println("\nStarting Test 2...");
        tester.test2(new SuffixTrie("hahaa"));
        System.out.println("\nStarting Test 3...");
        tester.test3(new SuffixTrie("abcdefghijklmnopqrstuvwxyz"));
        System.out.println("\nStarting Test 4...");
        tester.test4(new SuffixTrie("abcdLONGESTREPEATefghLONGESTREPEATijkl"));
        System.out.println("\nStarting Test 5...");
        tester.test5(new SuffixTrie(t5_thousand));

        System.out.println("\nPress ENTER to perform the five Tree tests...");
        sc.nextLine();

        testDetails = "Tree";
        System.out.println("Starting Test 1...");
        tester.test1(new SuffixTree(""));
        System.out.println("\nStarting Test 2...");
        tester.test2(new SuffixTree("hahaa"));
        System.out.println("\nStarting Test 3...");
        tester.test3(new SuffixTree("abcdefghijklmnopqrstuvwxyz"));
        System.out.println("\nStarting Test 4...");
        tester.test4(new SuffixTree("abcdLONGESTREPEATefghLONGESTREPEATijkl"));
        System.out.println("\nStarting Test 5...");
        tester.test5(new SuffixTree(t5_thousand));
    }

    private void test1(final GeneralSuffixTree tree) {

        System.out.println("Test 1 started. (" + testDetails +")");
        tree.show();

        // SUBSTRING, SUFFIX, COUNT
        assert tree.substring("");
        assert tree.suffix("");
        assert tree.count("") == 1;

        // LONGEST REPEAT AND LONGEST SUBSTRING
        assert tree.longestRepeat().equals("");
        assert tree.longestSubstring("abcdefghijklmnopqrstuvwxyz").equals("");

        System.out.println("Test 1 ended successfully.");
    }

    private void test2(final GeneralSuffixTree tree) {

        System.out.println("Test 2 started. (" + testDetails +")");
        tree.show();

        // Strings to be used
        int str1Index;
        final String hahaaStr[] = {"", "h", "ha", "hah", "haha", "hahaa", "ahaa", "haa", "aa", "a", "aha", "bahaha"};
        final int counts[] = {6, 2, 2, 1, 1, 1, 1, 1, 1, 3, 1, 0};

        // SUBSTRING
        for (str1Index = 0; str1Index < hahaaStr.length - 1; str1Index++) { // loop skips "bahaha"
            assert tree.substring(hahaaStr[str1Index]);
        }
        assert !tree.substring(hahaaStr[str1Index++]); // "bahaha"
        assert str1Index == hahaaStr.length; // verifies that all strings checked

        // SUFFIX
        str1Index = 0;
        assert tree.suffix(hahaaStr[str1Index++]);
        assert !tree.suffix(hahaaStr[str1Index++]);
        assert !tree.suffix(hahaaStr[str1Index++]);
        assert !tree.suffix(hahaaStr[str1Index++]);
        assert !tree.suffix(hahaaStr[str1Index++]);
        assert tree.suffix(hahaaStr[str1Index++]);
        assert tree.suffix(hahaaStr[str1Index++]);
        assert tree.suffix(hahaaStr[str1Index++]);
        assert tree.suffix(hahaaStr[str1Index++]);
        assert tree.suffix(hahaaStr[str1Index++]);
        assert !tree.suffix(hahaaStr[str1Index++]);
        assert !tree.suffix(hahaaStr[str1Index++]);
        assert str1Index == hahaaStr.length; // verifies that all strings checked

        // COUNT
        for (str1Index = 0; str1Index < hahaaStr.length; str1Index++) {
            assert tree.count(hahaaStr[str1Index]) == counts[str1Index];
        }
        assert str1Index == hahaaStr.length; // verifies that all strings checked

        // LONGEST REPEAT AND LONGEST SUBSTRING
        assert tree.longestRepeat().equals("ha");
        assert tree.longestSubstring("bahaha").equals("haha");

        System.out.println("Test 2 ended successfully.");
    }

    private void test3(final GeneralSuffixTree tree) {

        System.out.println("Test 3 started. (" + testDetails +")");
        tree.show();

        // LONGEST REPEAT AND LONGEST SUBSTRING
        assert tree.longestRepeat().equals("");
        assert tree.longestSubstring("zyxw").equals("z");

        System.out.println("Test 3 ended successfully.");
    }

    private void test4(final GeneralSuffixTree tree) {

        System.out.println("Test 4 started. (" + testDetails +")");
        tree.show();

        // LONGEST REPEAT AND LONGEST SUBSTRING
        assert tree.longestRepeat().equals("LONGESTREPEAT");
        assert tree.longestSubstring("ijklLONGESTREPEATabcd").equals("LONGESTREPEAT");

        System.out.println("Test 4 ended successfully.");
    }

    private void test5(final GeneralSuffixTree tree) {

        System.out.println("Test 5 started. (" + testDetails +")");
        if (tree instanceof SuffixTrie) {
            System.out.println("The suffix trie for this test was not be displayed due to its size.");
        } else {
            tree.show();
        }

        // Strings to be used
        final String t5_thousand_secondhalf = t5_thousand.substring(t5_thousand.length() / 2, t5_thousand.length());
        final String t5_thousand_substrings[] = {
                t5_thousand.substring(50, 100),   // 50  characters
                t5_thousand.substring(200, 300),  // 100 characters
                t5_thousand.substring(400, 600)   // 200 characters
        };

        // SUFFIX
        assert tree.suffix(t5_thousand_secondhalf);
        assert !tree.suffix(t5_thousand_substrings[0]);
        assert !tree.suffix(t5_thousand_substrings[1]);
        assert !tree.suffix(t5_thousand_substrings[2]);

        // SUBSTRING
        assert tree.substring(t5_thousand_secondhalf);
        assert tree.substring(t5_thousand_substrings[0]);
        assert tree.substring(t5_thousand_substrings[1]);
        assert tree.substring(t5_thousand_substrings[2]);

        // COUNT
        assert tree.count(t5_thousand_secondhalf) == 1;
        assert tree.count(t5_thousand_substrings[0]) == 1;
        assert tree.count(t5_thousand_substrings[1]) == 1;
        assert tree.count(t5_thousand_substrings[2]) == 1;
        assert tree.count(t5_thousand_longRepeat) == 2;

        // LONGEST REPEAT AND LONGEST SUBSTRING
        assert tree.longestRepeat().equals(t5_thousand_longRepeat);
        assert tree.longestSubstring(t5_thousand_substrings[1] + t5_thousand_substrings[2] + t5_thousand_substrings[0]).equals(t5_thousand_substrings[2]);

        System.out.println("Test 5 ended successfully.");
    }
}

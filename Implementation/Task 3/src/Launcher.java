import suffixtree.optimized.SuffixTree;
import suffixtree.unoptimized.SuffixTrie;
import suffixtree.GeneralSuffixTree;

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Launcher {

    public static void main(String args[]) {

        final String fnOptions[] = {"substr", "suffix", "count", "lonrep", "lonsub", "show"};

        if (args.length == 2 || args.length == 3) {
            
            final Pattern p = Pattern.compile("^(\\S+[.][a-z]+) ([a-z]+) ([a-z]*)$");
            final Matcher m = p.matcher(args[0] + " " + args[1] + " " + (args.length > 2 ? args[2] : ""));

            if (m.find()) {

                GeneralSuffixTree tree;
                final String filename = m.group(1);
                final String function = m.group(2);
                final String argument = m.group(3);

                // Read string for tree from file
                try (final BufferedReader br = new BufferedReader(new FileReader(filename))) {
                    System.out.println("Opened \"" + filename + "\".");
                    String treeString = br.readLine();

                    // Assume blank string if no string found
                    if (treeString == null) {
                        System.out.println("No string found; assuming a blank string.");
                        treeString = "";
                    }

                    // Create suffix trie or suffix tree
                    if ((int) (Math.random() * 2) == 0) {
                        tree = new SuffixTrie(treeString);
                        System.out.println("Created suffix trie based on \"" + treeString + "\".");
                    } else {
                        tree = new SuffixTree(treeString);
                        System.out.println("Created suffix tree based on \"" + treeString + "\".");
                    }
                } catch (FileNotFoundException fnfe) {
                    System.out.println("File \"" + filename + "\" was not found.");
                    return;
                } catch (IOException ioe) {
                    System.out.println("IO error when opening file \"" + filename + "\".");
                    ioe.printStackTrace();
                    return;
                }

                // Change function choice to integer representation
                int fnChoice = -1;
                for (int i = 0; i < fnOptions.length; i++) {
                    if (function.equals(fnOptions[i])) {
                        fnChoice = i;
                    }
                }

                // Optional argument to be applied
                System.out.println("Argument: \"" + argument + "\"");

                System.out.print("Result: ");
                switch (fnChoice) {
                    case 0:
                        System.out.println(tree.substring(argument) ? "Yes, it's a substring." : "No, it's not a substring.");
                        break;
                    case 1:
                        System.out.println(tree.suffix(argument) ? "Yes, it's a suffix." : "No, it's not a suffix.");
                        break;
                    case 2:
                        System.out.println("Count: " + tree.count(argument));
                        break;
                    case 3:
                        System.out.println("Longest repeat: " + tree.longestRepeat());
                        checkForFinalArgument(argument);
                        break;
                    case 4:
                        System.out.println("Longest substring: " + tree.longestSubstring(argument));
                        break;
                    case 5:
                        System.out.println();
                        tree.show();
                        checkForFinalArgument(argument);
                        break;
                    default:
                        System.out.println("Invalid function.\nExpected: \"<filename> <function> <optional argument>\"");
                        printExpected(fnOptions);
                }
            } else {
                System.out.println("Invalid format.\nExpected: \"<filename> <function> <optional argument>\"");
                printExpected(fnOptions);
            }
        } else {
            System.out.println("Invalid number of inputs.\nExpected: \"<filename> <function> <optional argument>\"");
            printExpected(fnOptions);
        }
    }

    private static void checkForFinalArgument(final String arg) {

        if (arg.length() > 0) {
            System.out.println("Third argument ignored since chosen function does not have a parameter.");
        }
    }

    private static void printExpected(final String fnOptions[]) {

        System.out.println("\t<filename> = <string>.txt");
        System.out.println("\t<function> =  " + fnOptions[0] + "\t=>  check if suffix (requires argument)\n" +
                "           or " + fnOptions[1] + "\t=>  check if substring (requires argument)\n" +
                "           or " + fnOptions[2] + "\t=>  find substring count (requires argument)\n" +
                "           or " + fnOptions[3] + "\t=>  find longest repeat\n" +
                "           or " + fnOptions[4] + "\t=>  find longest substring (requires argument)\n" +
                "           or " + fnOptions[5] + "\t=>  displays suffix tree");
        System.out.println("\t<optional argument> = <string> (if function requires argument; Otherwise blank)");
    }
}

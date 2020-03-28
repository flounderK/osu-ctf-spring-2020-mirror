public class SuperDuperSecureFlagValidator {
    private static boolean checkFlag(String candidate) {
        try {
            //starts with "osuctf{"
            if (!candidate.substring(0, 7).equals("osuctf{")) {
                return false;
            }

            //ends with }
            if (candidate.charAt(candidate.length() - 1) != '}') {
                return false;
            }

            // split on _
            StringTokenizer st = new StringTokenizer(
                    candidate.substring(7, candidate.length() - 1), "_");

            // first word conds
            if (!Validator1.verify(st.nextToken())) {
                return false;
                // first char is not '0' (zero)
            }

            if (!Validator2.verify(st.nextToken())) {
                return false;
                // length == 7
                // 4:7 "7h2"
                // F3jk7h2
            }

            // is two words in a format like "one_two"
            if (st.hasMoreTokens()) {
                return false;
            }
            return true;
        } catch (Exception e) {
            return false;
        } 
    }

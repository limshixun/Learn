// The value in the grid is defined as the lowest number of steps to get from [char 0 to i] to [char 0 to j]
// We can derive the current lowest by looking at how neighbours get there, like a tree.
//
// Source (Rows) = CAT
// Target (Cols) = CUT
//
// [  ",C,U,T
// " [0,1,2,3],
// C [1,0,1,2],
// A [2,C,N,N],
// T [3,N,N,N]
// ]
// N = NULL, C = CURRENT
//
// To get from "ca" to "c", we can either:
// 1. Look left (INSERTION): "ca" to "" takes 2 deletion, and then add "c" so 3 steps total;
// e.g. "ca" ==2=> "" ==(INSERT C)=> "c"
// 2. Look up (DELETION): "c" to "c" takes 0 steps, and then delete "a" in "ca" so 1 steps total,
// e.g. "ca" ==(DELETE A)=> "c" ==0=> "c"
// 3. Look top left (SUBSTITUTION): c to "" takes 1 deletion, and then substitute "a" to "c" so 2 steps total,
// e.g. "ca" ==1=> "a" ==1=> "c"

const distance = (word1, word2) => {
  let matrix = Array(word1.length + 1)
    .fill(null)
    .map(() => Array(word2.length + 1).fill(null));

  for (let i = 0; i <= word1.length; i++) matrix[i][0] = i;
  for (let i = 0; i <= word2.length; i++) matrix[0][i] = i;

  for (let i = 1; i <= word1.length; i++) {
    for (let j = 1; j <= word2.length; j++) {
      const isEqual = word1[i - 1] === word2[j - 1] ? 0 : 1;
      matrix[i][j] = Math.min(
        //
        matrix[i - 1][j] + 1,
        //
        matrix[i][j - 1] + 1,
        //
        matrix[i - 1][j - 1] + isEqual
      );
    }
  }
  return matrix[word1.length][word2.length];
};

const optimizedLevenshtein = (word1, word2) => {
  const source_len = word1.length;
  const target_len = word2.length;

  let previousRow = Array.from({ length: target_len + 1 }, (_, i) => i);
  let currentRow = Array.from({ length: target_len + 1 }, () => 0);

  for (let i = 1; i <= source_len; i++) {
    currentRow[0] = i;
    for (let j = 1; j <= target_len; j++) {
      if (word2[j - 1] === word1[j - 1]) {
        currentRow[j] = previousRow[j - 1];
      } else {
        currentRow[j] = Math.min(currentRow[j - 1], previousRow[j], previousRow[j - 1]) + 1;
      }
    }
    previousRow = [...currentRow];
  }
  return previousRow[target_len];
};

// The value in the grid is defined as the lowest number of steps to get from [char 0 to i] to [char 0 to j]
// We can derive the current lowest by looking at how neighbours get there, like a tree.
//
// Source (Rows) = C, U, T
// Target (Cols) = C, A, T
//
//    [  ", C, A, T ]
// "" [ 0, 1, 2, 3 ]
// C  [ 1, 0, 1, 2 ]  <-- (Row C, Col A: "C" to "CA" takes 1 insertion)
// U  [ 2, C, N, N ]  <-- C = CURRENT (Row U, Col C: Comparing "CU" to "C")
// ]
// N = NULL, C = CURRENT
//
// To get from source "CU" to target "C" (at cell CURRENT), we look at our 3 neighbors:
//
// 1. Look UP (DELETION from Source):
//    The cell above is "C" to "C" (0 steps).
//    We take that 0, and DELETE the "U" from our source "CU".
//    Formula: 0 steps + 1 deletion = 1 step total.
//    e.g. "CU" ==(delete U)==> "C" ==(0 steps)==> "C"
//
// 2. Look LEFT (INSERTION to Target):
//    The cell left is "CU" to "" (2 steps: deleting C and U).
//    We take those 2 steps, and INSERT a "C" to match the target.
//    Formula: 2 steps + 1 insertion = 3 steps total.
//    e.g. "CU" ==(delete C,U)==> "" ==(insert C)==> "C"
//
// 3. Look TOP-LEFT (SUBSTITUTION):
//    The diagonal cell is "C" to "" (1 step: deleting C).
//    We take that 1 step, and SUBSTITUTE the source "U" for the target "C".
//    Formula: 1 step + 1 substitution = 2 steps total.
//    e.g. "CU" ==(delete C)==> "U" ==(sub U->C)==> "C"
//
// Final Winner for Cell CURRENT: Min(1, 3, 2) = 1 step.

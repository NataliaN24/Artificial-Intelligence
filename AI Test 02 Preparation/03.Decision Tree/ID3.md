Decision Tree (ID3) — the logic (how it works)

A decision tree is a classifier represented as a tree:

internal node = tests an attribute

branch = one value of that attribute

leaf = final class prediction 

08 Decision Tree

Most important functions (your “must-have” toolkit)

If you implement ID3 cleanly, these are the functions that matter most:

entropy(S)
Input: list of labeled samples
Output: impurity 
𝐻
(
𝑆
)
H(S)

splitByAttribute(S, A)
Output: map value -> subset

informationGain(S, A)
Uses entropy(S) + entropy of each subset from splitByAttribute

chooseBestAttribute(S, attributes)
Return attribute with max informationGain

majorityClass(S)
Used for empty splits / no attributes left

buildTree(S, attributes, default) (recursive ID3 / DTL)
This is the main ID3 loop described in the lecture 

Chapter18

.

predict(tree, x)
Walk down the tree using attribute values until leaf.

accuracy(tree, testSet)
Count correct / total.

kFoldSplit(data, k, shuffle) + crossValidate(data, k)
The homework in the slides explicitly asks 10-fold CV + accuracy per fold + mean 

08 Decision Tree

.

(Optional but common for overfitting control) prePruneK(S, K)
Stop splitting if |S| < K and return majorityClass(S) (matches the “constant K minimum examples” requirement 

08 Decision Tree

).

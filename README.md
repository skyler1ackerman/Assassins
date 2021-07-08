# Assassins
## Purpose
The purpose of this code was to answer a question that I have had for a long while. If you play a game of [assassins](https://en.wikipedia.org/wiki/Assassin_(game)), or draw for a Secret Santa, what are the odds that you get one large circle? Two circles? Three? These programs run many games of assassins and show the number of times each outcome happens, showing an empirical outcome to this question. This has been used by myself to test various theroies and estimations of a true mathematical representation.

## Derangements

Well it turns out that figuring out the odds of one circle is not that particularly difficult. You simply need to apply the formula for a derangements (which in themselves are actually incredibly complicated.) Basically, a derangement is when you rearrange a list of items, and none of the items end up in the same place that they originally started. As it turns out, this is exactly the same as a valid game of assassins, no one drew their own name. To see the formula and explanation of derangements see [here](https://en.wikipedia.org/wiki/Derangement)

## Continued Search

Unfortunately, predicting the probability of X number of circles given N players is a much harder question to answer once X > 1. If you have a decent answer, please contact me. I have been to four different University Professors from 3 Universities and none of them have been able to give me an answer that fit either with my intuition or with my empirical measurements. If you see an issue with the way I pull my data, please let me know. It should be noted that the two versions of the code pick in different ways. I have not found that this matters in any large amount. 
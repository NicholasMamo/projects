% grammar
s --> np, !. % for now, a sentence is only made up of a noun phrase
np --> sd, !, sn.
np --> pd, !, pn.
np --> sn.
np --> pn.

% lexicon
sd --> [a].
sd --> [the].
pd --> [the].
sn --> [dog].
sn --> [cat].
pn --> [dogs].
pn --> [cats].

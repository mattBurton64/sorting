% Facts
male(Allen).
female(Anne).
male(Brian).
female(Elizabeth).
male(Harold).
female(Marie).
male(David).
female(Christine).
female(Grace).
male(Leonard).
female(Kate).
male(Arthur).
female(Naomi).
male(Oliver).
female(Tracey).
male(Peter).
female(Irene).
male(Frank).
female(Rachel).
female(Nancy).
male(Steve).
female(Jane).
male(Jeremy).
female(Shannon).
male(Zach).
female(Jennifer).
male(Tom).
male(Jason).
female(Belinda).
male(Michael).
female(Susan).

parent(Allen, Grace).
parent(Allen, Kate).
parent(Anne, Grace).
parent(Anne, Kate).
parent(Brian, Leonard).
parent(Brian, Naomi).
parent(Elizabeth, Leonard).
parent(Elizabeth, Naomi).
parent(Harold, Oliver).
parent(Harold, Tracey).
parent(Marie, Oliver).
parent(Marie, Tracey).
parent(David, Arthur).
parent(David, Peter).
parent(Christine, Arthur).
parent(Christine, Peter).
parent(Grace, Irene).
parent(Grace, Frank).
parent(Leonard, Irene).
parent(Leonard, Frank).
parent(Kate, Rachel).
parent(Kate, Nancy).
parent(Arthur, Rachel).
parent(Arthur, Nancy).
parent(Naomi, Steve).
parent(Naomi, Jane).
parent(Oliver, Steve).
parent(Oliver, Jane).
parent(Tracey, Jeremy).
parent(Peter, Jeremy).
parent(Frank, Shannon).
parent(Frank, Zach).
parent(Frank, Jennifer).
parent(Rachel, Shannon).
parent(Rachel, Zach).
parent(Rachel, Jennifer).
parent(Nancy, Tom).
parent(Nancy, Jason).
parent(Nancy, Belinda).
parent(Steve, Tom).
parent(Steve, Jason).
parent(Steve, Belinda).
parent(Jane, Michael).
parent(Jane, Susan).
parent(Jeremy, Michael).
parent(Jeremy, Susan).

% Rules
% A spouse is a parent who shares a child with another parent, where the two parents are not the same person
spouse(X, Y) :- parent(X, Z), parent(Y, Z), X \= Y.

% A mother is a parent who is also a female
mother(X, Y) :- parent(X, Y), female(X). 

% A father is a parent who is also a male
father(X, Y) :- parent(X , Y), male(X).

% A sibling shares a parent and is not the same person
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% A brother is a sibling who is also a male
brother(X, Y) :- sibling(X, Y), male(X).

% A sister is a sibling who is also a female
sister(X, Y) :- sibling(X, Y), female(X).

% A son is the child of a parent who is also a male
son(X, Y) :- parent(Y, X), male(X).

% A doughter is the child of a parent who is also a female
daughter(X, Y) :- parent(Y, X), female(X).

% A grandfather is a parent of a parent who is also a male
grandfather(X, Y) :- parent(X, Z), parent(Z, Y), male(X).

% A grandmother is a parent of a parent who is also a female
grandmother(X, Y) :- parent(X, Z), parent(Z, Y), female(X).

% An aunt is a sister of a parent
aunt(X, Y) :- sister(X, Z), parent(Z, Y).

% An uncle is a brother of a parent
uncle(X, Y) :- brother(X, Z), parent(Z, Y).

% A cousin is the child of a parent whos sibling is the parent of X
cousin(X, Y) :- parent(Z, X), parent(W, Y), sibling(Z, W).
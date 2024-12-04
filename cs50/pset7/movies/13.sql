SELECT people.name
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name != "Kevin Bacon"
AND movies.id IN
    (
    SELECT movies.id
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = "Kevin Bacon" 
    AND people.birth = 1958
    )
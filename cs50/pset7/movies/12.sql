SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Bradley Cooper" 
OR people.name = "Jennifer Lawrence"
GROUP BY movies.id
HAVING COUNT(movies.id) > 1;
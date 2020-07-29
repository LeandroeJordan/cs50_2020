select p.name from stars s join people p on s.person_id = p.id
where s.movie_id in (select m.id from movies m where year = 2004) order by birth asc;
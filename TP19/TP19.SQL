SELECT name FROM villagers WHERE color = 'Red';

SELECT DISTINCT color FROM villagers ;

SELECT name FROM villagers WHERE color = 'Green' AND birthday = '06-25';

SELECT name FROM wallpapers ORDER BY price LIMIT 7 OFFSET 3;

SELECT DISTINCT name FROM articles ORDER BY price LIMIT 10

SELECT date FROM purchases WHERE amount = 7



SELECT date FROM purchases WHERE amount != 7
INTERSECT
SELECT birthday FROM villagers WHERE style='Cool'


SELECT v1.name FROM villagers as v1
JOIN referral as r ON r.id_referrer = v1.id
JOIN villagers  as v2 ON r.id_referee = v2.id
WHERE v2.name = 'Charlise'


SELECT v1.name FROM villagers as v1
JOIN referral as r ON r.id_referrer = v1.id
WHERE r.id_referee = r.id_referrer


SELECT sum(p.amount) FROM
purchases as p 
JOIN villagers as v ON p.villager_id = v.id
WHERE v.birthday = p.date


SELECT DISTINCT v.name FROM
purchases as p 
JOIN villagers as v ON p.villager_id = v.id
JOIN articles as a ON a.id = p.article_id AND p.variant_id = a.variant_id
WHERE v.color != a.color


SELECT DISTINCT name FROM villagers
EXCEPT
SELECT DISTINCT v.name FROM
purchases as p 
JOIN villagers as v ON p.villager_id = v.id
JOIN articles as a ON a.id = p.article_id AND p.variant_id = a.variant_id
WHERE v.color = a.color



SELECT DISTINCT v.name ,sum(p.amount), min(a.price), max(a.price) FROM
purchases as p 
JOIN villagers as v ON p.villager_id = v.id
JOIN articles as a ON a.id = p.article_id
GROUP BY v.name
rf

SELECT species, color, style, count(species)  as c from villagers group by species, color, style  order by c desc limit 4





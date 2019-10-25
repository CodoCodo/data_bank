CREATE TABLE IF NOT EXISTS simple_labels (
  id INT NOT NULL AUTO_INCREMENT,
  media_id INT NOT NULL,
  frame_id INT NOT NULL,
  label_str VARCHAR(64) NOT NULL,
  PRIMARY KEY(id, media_id, frame_id)
);


const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

mongoose.connect('mongodb://127.0.0.1:27017/studentDB')
  .then(() => console.log('MongoDB connected successfully'))
  .catch((err) => console.error('MongoDB connection error:', err));

const studentSchema = new mongoose.Schema({
  stID: { type: String, required: true, unique: true },
  name: { type: String, required: true },
  gender: { type: String, required: true },
  email: { type: String, required: true },
  studyProgram: { type: String, required: true },
  yearOfStudy: { type: Number, required: true }
});

const Student = mongoose.model('Student', studentSchema);

app.get('/students', async (req, res) => {
  res.json(await Student.find());
});

app.post('/students', async (req, res) => {
  res.status(201).json(await new Student(req.body).save());
});

app.put('/students/:stID', async (req, res) => {
  res.json(await Student.findOneAndUpdate({ stID: req.params.stID }, req.body, { new: true }));
});

app.delete('/students/:stID', async (req, res) => {
  res.json(await Student.findOneAndDelete({ stID: req.params.stID }));
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));

const mongoose = require("mongoose");

const doctorSchema = new mongoose.Schema({
  userId: { type: mongoose.Schema.Types.ObjectId, ref: "User", required: true },
  name: { type: String, required: true },
  specialty: { type: String, required: true },
  availability: [
    {
      date: String,
      startTime: String,
      endTime: String,
    },
  ],
});

module.exports = mongoose.model("Doctor", doctorSchema);

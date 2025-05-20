const mongoose = require("mongoose");

const appointmentSchema = new mongoose.Schema({
  patientId: {
    type: mongoose.Schema.Types.ObjectId,
    ref: "Patient",
    required: true,
  },
  doctorId: {
    type: mongoose.Schema.Types.ObjectId,
    ref: "Doctor",
    required: true,
  },
  date: { type: String, required: true },
  startTime: { type: String, required: true },
  endTime: { type: String },
  status: {
    type: String,
    enum: ["pending", "confirmed", "canceled"],
    default: "pending",
  },
  createdBy: { type: mongoose.Schema.Types.ObjectId, ref: "User" },
  confirmedBy: { type: mongoose.Schema.Types.ObjectId, ref: "User" },
  canceledBy: { type: mongoose.Schema.Types.ObjectId, ref: "User" },
});

module.exports = mongoose.model("Appointment", appointmentSchema);
